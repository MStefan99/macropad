#include "src/macropad.hpp"

#define OLED_MOSI 27
#define OLED_CLK  26
#define OLED_DC   24
#define OLED_CS   22
#define OLED_RST  23

#define LED_PIN        13
#define NEOPIXEL_PIN   19
#define NEOPIXEL_COUNT 12


// Options
constexpr static uint32_t keyDebounceTime {5};
constexpr static uint32_t encoderDebounceTime {2};
constexpr static uint32_t longPressDuration {750};
constexpr static uint32_t transitionDuration {500};


// Static
enum class PluginState : uint8_t {
	New = 0,
	Activated = 1,
	Resumed = 2,
	Suspended = 3,
	Deactivated = 4
};

struct PluginInfo {
	Plugin*     plugin;
	PluginState state;
};

constexpr static int8_t encoderTransitions[4][4] {
  {0,  -1, 1,  0 },
  {1,  0,  0,  -1},
  {-1, 0,  0,  1 },
  {0,  1,  -1, 0 }
};

// Gamma correction can be too eager to clip the brightness to 0
// This table adds an offset to correct for that
constexpr static uint8_t brightnessTable[32] {0,   25,  32,  40,  48,  55,  63,  71,  78,  86,  94,
                                              101, 109, 117, 124, 132, 140, 147, 155, 163, 170, 178,
                                              186, 193, 201, 209, 216, 224, 232, 239, 247, 255};


static Adafruit_SH1106G  display = Adafruit_SH1106G(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);
static Adafruit_NeoPixel strip(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


// State
static bool updateDisplay {false};
static bool showBacklight {false};

static PinStatus pinStatuses[13] {};
static uint32_t  pinTimes[13] {};
static uint8_t   skipButtonRelease = ~0;

static uint8_t  encoderPosition {0};
static int32_t  encoderCount {0};
static int32_t  sentEncoderCount {0};
static uint32_t encoderTime {0};

static PluginInfo pluginStack[16] {};
static uint8_t    activePluginCount {0};
static uint32_t   lastAction {0};
static bool       idle {false};
static bool       suspended {true};

static uint8_t  dispatchQueue[8] {0};
static uint16_t dispatchConsumer {0};
static bool     dispatched {false};
static uint32_t dispatchStart {0};
static uint32_t dispatchDuration {0};

static uint8_t  outString[64] {0};
static uint8_t* outChar {outString};

static char    serialBuffer[32] {};
static uint8_t serialIdx {0};

static uint32_t transitionStart {0};
static bool     transitionActive {true};


void displayPlugin();
void setBacklight();
void dispatchKeys(const uint8_t keys[8], uint16_t consumerKey, uint32_t duration);
void typeString(const char* string, uint8_t len, uint32_t delay);
void activatePlugin(Plugin* plugin);
void deactivatePlugin();

bool rewindState(PluginInfo& info, PluginState targetState) {
	while (info.state != targetState) {
		switch (info.state) {
			case PluginState::New:
				info.plugin->onActivate();
				info.state = PluginState::Activated;
				break;
			case PluginState::Activated:
				info.plugin->onResume();
				info.state = PluginState::Resumed;
				break;
			case PluginState::Resumed:
				info.plugin->onSuspend();
				info.state = PluginState::Suspended;
				break;
			case PluginState::Suspended:
				if (targetState == PluginState::Deactivated) {
					info.plugin->onDeactivate();
					info.state = PluginState::Deactivated;
				} else {
					info.plugin->onResume();
					info.state = PluginState::Resumed;
				}
				break;
			case PluginState::Deactivated:
				if (targetState == PluginState::New) {
					return false;
				}
				info.plugin->onActivate();
				info.state = PluginState::Activated;
				break;
		}
	}

	return true;
}

CanvasProvider    canvasProvider {displayPlugin};
BacklightProvider backlightProvider {setBacklight};
KeyDispatcher     keyDispatcher {dispatchKeys, typeString};
PluginEnvironment pluginEnvironment {canvasProvider, backlightProvider, keyDispatcher};

Navigator navigator(activatePlugin, deactivatePlugin);

// Called from interrupts
void displayPlugin() {
	updateDisplay = true;
}

// Called from interrupts
void setBacklight() {
	showBacklight = true;
}

// Called from interrupts
void dispatchKeys(const uint8_t keys[8], uint16_t consumerKey, uint32_t duration) {
	uint8_t i {0};
	for (; i < sizeof(dispatchQueue) - 1 && keys[i]; ++i) {
		dispatchQueue[i] = keys[i];
	}
	dispatchQueue[i] = 0;

	dispatchConsumer = consumerKey;
	dispatchDuration = duration;
}

// Called from interrupts
void typeString(const char* str, uint8_t len, uint32_t delay) {
	uint8_t i {0};
	for (; i < len && i < sizeof(outString) - 1 && str[i]; ++i) {
		outString[i] = str[i];
	}
	outString[i] = 0;
	outChar = outString;

	dispatchDuration = delay;
}

// Called from interrupts
void buttonHandler(void* pinPtr) {
	uint8_t pin {static_cast<uint8_t>(reinterpret_cast<int>(pinPtr))};
	auto    status = digitalRead(pin);

	if (status == pinStatuses[pin]) {
		return;
	}
	pinStatuses[pin] = status;

	auto pinTime = pinTimes[pin];
	if (millis() - pinTime < keyDebounceTime) {
		return;
	}
	pinTimes[pin] = millis();

	if (suspended) {
		return;
	}

	if (status && pin == skipButtonRelease) {
		skipButtonRelease = ~0;
		return;
	}

	if (idle) {
		skipButtonRelease = pin;
		lastAction = millis();
		return;
	}

	if (activePluginCount) {
		lastAction = millis();

		if (!status) {
			if (pin) {  // Defer encoder until release due to long pressitaita
				pluginStack[activePluginCount - 1].plugin->onKeyDown(pin);
			}
		} else {
			if (!pin) {  // Dispatch deferred encoder press
				pluginStack[activePluginCount - 1].plugin->onKeyDown(pin);
			}
			pluginStack[activePluginCount - 1].plugin->onKeyUp(pin);
		}
	}
}

// Called from interrupts
void encoderHandler(void* pinPtr) {
	uint8_t newPosition = (static_cast<uint8_t>(digitalRead(17)) << 1) | (static_cast<uint8_t>(digitalRead(18)));
	int8_t  transition = -encoderTransitions[encoderPosition][newPosition];
	encoderCount += transition;
	encoderPosition = newPosition;

	auto lastEncoderTime {encoderTime};
	if (millis() - lastEncoderTime < encoderDebounceTime) {
		return;
	}
	encoderTime = millis();

	if (suspended) {
		return;
	}

	lastAction = millis();

	if (idle) {
		displayPlugin();
		setBacklight();
		return;
	}

	int32_t count = encoderCount / settingsProvider::getSettings().encoderDivisor;
	if (transition && count != sentEncoderCount) {
		sentEncoderCount = count;
		if (!pinStatuses[0] && tud_ready()) {  // Setting brightness
			auto settings {settingsProvider::getSettings()};
			settings.brightness = min(max(settings.brightness + transition, 0), 31);
			settingsProvider::setSettings(settings);

			skipButtonRelease = 0;
			setBacklight();
		} else if (activePluginCount) {
			if (transition > 0) {
				pluginStack[activePluginCount - 1].plugin->onEncoderUp(count);
			} else {
				pluginStack[activePluginCount - 1].plugin->onEncoderDown(count);
			}
		}
	}
}

void drawPluginName() {
	if (!activePluginCount) {
		return;
	}

	display.fillRect(0, 0, 128, 8, SH110X_WHITE);
	display.setTextColor(SH110X_BLACK);

	int16_t  x, y;
	uint16_t w, h;
	display.getTextBounds(pluginStack[activePluginCount - 1].plugin->getDisplayName(), 0, 0, &x, &y, &w, &h);

	display.setCursor(64 - w / 2, 0);
	display.print(pluginStack[activePluginCount - 1].plugin->getDisplayName());
}

void activatePlugin(Plugin* plugin) {
	if (activePluginCount > sizeof(pluginStack) / sizeof(pluginStack[0])) {
		return;
	}

	encoderCount = 0;

	suspendPlugin();

	pluginStack[activePluginCount].plugin = plugin;
	pluginStack[activePluginCount].state = PluginState::New;
	++activePluginCount;

	rewindState(pluginStack[activePluginCount - 1], PluginState::Activated);

	if (!idle && !suspended) {
		rewindState(pluginStack[activePluginCount - 1], PluginState::Resumed);
		display.clearDisplay();
		drawPluginName();
		display.display();
	}
}

void suspendPlugin() {
	if (!activePluginCount) {
		return;
	}

	rewindState(pluginStack[activePluginCount - 1], PluginState::Suspended);
}

void resumePlugin() {
	if (!activePluginCount) {
		return;
	}

	rewindState(pluginStack[activePluginCount - 1], PluginState::Resumed);

	display.clearDisplay();
	drawPluginName();
	display.display();
}

void deactivatePlugin() {
	if (!activePluginCount) {
		return;
	}

	rewindState(pluginStack[activePluginCount-- - 1], PluginState::Deactivated);
	resumePlugin();
}

void setup() {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);

	for (uint8_t i {0}; i <= 12; ++i) {
		pinMode(i, INPUT_PULLUP);
		pinStatuses[i] = PinStatus::HIGH;
		attachInterrupt(digitalPinToInterrupt(i), buttonHandler, PinStatus::CHANGE, reinterpret_cast<void*>(i));
	}

	for (uint8_t i {17}; i <= 18; ++i) {
		pinMode(i, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(i), encoderHandler, PinStatus::CHANGE, reinterpret_cast<void*>(i));
	}

	Serial.begin(115200);

	Keyboard.begin();

	strip.begin();
	strip.show();

	display.begin(0, true);
	display.drawBitmap(0, 0, reinterpret_cast<const uint8_t*>(icons::macropad), 128, 64, SH110X_WHITE, SH110X_BLACK);
	display.display();
	delay(1000);

	if (!tud_ready()) {
		display.fillScreen(SH110X_BLACK);
		display.display();
	}

	populateAppsScreen();
	lastAction = transitionStart = millis();

	digitalWrite(LED_PIN, LOW);
}

void loop() {
	// Tick the plugin
	if (activePluginCount) {
		pluginStack[activePluginCount - 1].plugin->onTick();
	}

	// Dispatch keys
	if (!dispatched && (dispatchQueue[0] || dispatchConsumer)) {
		for (uint8_t i {0}; i < sizeof(dispatchQueue) && dispatchQueue[i]; ++i) {
			Keyboard.press(dispatchQueue[i]);
			dispatchQueue[i] = 0;
		}
		if (dispatchConsumer) {
			Keyboard.consumerPress(dispatchConsumer);
		}

		dispatchConsumer = 0;
		dispatchStart = millis();
		dispatched = true;
	}

	// Type string
	if (!dispatched && *outChar) {
		if (*outChar >= 0x41 && *outChar <= 0x5a) {  // Uppercase letters
			*outChar += 0x20;
			Keyboard.press(KEY_LEFT_SHIFT);
		}

		Keyboard.press(*outChar);
		dispatched = true;
		dispatchStart = millis();

		++outChar;
		if (!*outChar) {
			outString[0] = 0;
			outChar = outString;
		}
	}

	// Release keys
	if (dispatched && millis() - dispatchStart > dispatchDuration) {
		dispatched = false;
		Keyboard.releaseAll();
		Keyboard.consumerRelease();
	}

	// Open menu
	if (!suspended && !pinStatuses[0] && skipButtonRelease && millis() - pinTimes[0] > longPressDuration) {
		pinStatuses[0] = PinStatus::HIGH;

		if (!activePluginCount) {
			// Do nothing
		} else if (activePluginCount > 1) {
			deactivatePlugin();
		} else {
			activatePlugin(mainScreen);
		}
	}

	// Screen timeout
	auto screenTimeout {settingsProvider::getSettings().screenTimeout};
	if (!suspended) {
		if (!idle && millis() - lastAction > screenTimeout) {
			suspendPlugin();
			idle = true;
			transitionStart = millis() - screenTimeout;
			transitionActive = true;
			display.fillScreen(SH110X_BLACK);
			display.display();
			for (uint8_t i {0}; i < 12; ++i) {
				strip.setPixelColor(i, 0);
			}
			strip.show();
		} else if (idle && millis() - lastAction < screenTimeout) {
			idle = false;
			resumePlugin();
			lastAction = transitionStart = millis();
			transitionActive = true;
		}

		settingsProvider::commitSettings();

		// Update display
		if (!idle && updateDisplay) {
			updateDisplay = false;
			display.drawBitmap(
			    0,
			    8,
			    const_cast<const uint8_t*>(canvasProvider.getBuffer()),
			    128,
			    56,
			    SH110X_WHITE,
			    SH110X_BLACK
			);
			display.display();
		}
	}

	// Update backlight
	uint32_t transitionTime = millis() - transitionStart;
	uint32_t transitionProgress =
	    transitionTime < transitionDuration ? transitionTime : screenTimeout + transitionDuration - transitionTime;

	if (transitionProgress > transitionDuration) {
		transitionActive = false;
		if (transitionTime > screenTimeout) {
			for (uint8_t i {0}; i < 12; ++i) {
				strip.setPixelColor(i, 0);
			}
			strip.show();
		}
		if (lastAction > transitionStart) {
			transitionStart = lastAction;
		}
	}

	if (transitionActive) {
		uint8_t brightness =
		    brightnessTable[settingsProvider::getSettings().brightness] * transitionProgress / transitionDuration;

		for (uint8_t i {0}; i < 12; ++i) {
			auto color {backlightProvider.getPixel(i)};
			strip.setPixelColor(
			    i,
			    strip.gamma8((color.getR() * brightness) >> 8u),
			    strip.gamma8((color.getG() * brightness) >> 8u),
			    strip.gamma8((color.getB() * brightness) >> 8u)
			);
		}
		strip.show();
	} else if (!idle && showBacklight) {
		showBacklight = false;
		uint8_t brightness = brightnessTable[settingsProvider::getSettings().brightness];

		for (uint8_t i {0}; i < 12; ++i) {
			auto color {backlightProvider.getPixel(i)};
			strip.setPixelColor(
			    i,
			    strip.gamma8((color.getR() * brightness) >> 8u),
			    strip.gamma8((color.getG() * brightness) >> 8u),
			    strip.gamma8((color.getB() * brightness) >> 8u)
			);
		}
		strip.show();
	}

	// USB suspend
	if (!tud_ready() && !suspended) {
		suspendPlugin();
		suspended = true;

		display.fillScreen(SH110X_BLACK);
		display.display();

		if (!idle) {
			transitionStart = millis() - screenTimeout;
			transitionActive = true;
		}
	} else if (tud_ready() && suspended && pluginCount) {
		suspended = false;
		if (!activePluginCount) {  // Plugin initialization
			activatePlugin(plugins[0]);
		} else {
			resumePlugin();
		}
		idle = false;
		lastAction = transitionStart = millis();
		transitionActive = true;
	}

	// Serial commands
	if (Serial.available()) {
		auto byte {Serial.read()};
		serialBuffer[serialIdx++] = byte;

		if (!byte || byte == '\r' || byte == '\n') {
			if (!strncmp(serialBuffer, "a>", 2)) {
				if (activePluginCount == 1) {
					uint8_t foundIdx {0};
					bool    found {false};

					for (uint8_t i {0}; i < pluginCount; ++i) {
						if (!strncmp(serialBuffer + 2, plugins[i]->getName(), strlen(plugins[i]->getName()))) {
							foundIdx = i;
							found = true;
							break;
						}
					}

					auto switching {pluginStack[0].plugin != plugins[foundIdx]};

					if (switching) {
						deactivatePlugin();
						activatePlugin(plugins[foundIdx]);
					}

					Serial.print(found ? switching ? "a=" : "a:" : switching ? "a!" : "a~");
					Serial.println(pluginStack[0].plugin->getName());
				} else {
					Serial.println("a-");
				}
			}

			serialIdx = 0;
		}

		serialIdx = serialIdx % sizeof(serialBuffer);
	}

	delay(1);
}
