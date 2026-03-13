#include "src/macropad.hpp"

#define OLED_MOSI 27
#define OLED_CLK  26
#define OLED_DC   24
#define OLED_CS   22
#define OLED_RST  23

#define LED_PIN        13
#define NEOPIXEL_PIN   19
#define NEOPIXEL_COUNT 12


constexpr static uint32_t keyDebounceTime {5};
constexpr static uint32_t encoderDebounceTime {2};
constexpr static uint32_t longPressDuration {750};


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

static bool updateDisplay {false};
static bool showBacklight {false};

static PinStatus pinStatuses[13] {};
static uint32_t  pinTimes[13] {};
static uint8_t   skipButtonRelease = ~0;

static uint8_t  encoderPosition {0};
static int32_t  encoderCount {0};
static int32_t  sentEncoderCount {0};
static uint32_t encoderTime {0};

static Plugin*  pluginStack[16] {};
static uint8_t  activePluginCount {0};
static uint32_t lastAction {0};
static bool     idle {false};
static bool     suspended {false};

static uint8_t  dispatchQueue[8] {0};
static uint16_t dispatchConsumer {0};
static bool     dispatched {false};
static uint32_t dispatchStart {0};
static uint32_t dispatchDuration {0};

static char    serialBuffer[32] {};
static uint8_t serialIdx {0};


void displayPlugin();
void setBacklight();
void dispatchKeys(const uint8_t keys[8], uint16_t consumerKey, uint32_t duration);
void activatePlugin(Plugin* plugin);
void deactivatePlugin();


CanvasProvider    canvasProvider {displayPlugin};
BacklightProvider backlightProvider {setBacklight};
KeyDispatcher     keyDispatcher {dispatchKeys};
PluginEnvironment pluginEnvironment {canvasProvider, backlightProvider, keyDispatcher};

Navigator navigator(activatePlugin, deactivatePlugin);

// Called from interrupts
void displayPlugin() {
	updateDisplay = true;
	lastAction = millis();
}

// Called from interrupts
void setBacklight() {
	showBacklight = true;
	lastAction = millis();
}

// Called from interrupts
void dispatchKeys(const uint8_t keys[8], uint16_t consumerKey, uint32_t duration) {
	for (uint8_t i {0}; i < 6 && keys[i]; ++i) {
		dispatchQueue[i] = keys[i];
	}

	dispatchConsumer = consumerKey;
	dispatchDuration = duration;
	lastAction = millis();
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

	if (idle) {
		displayPlugin();
		setBacklight();
		skipButtonRelease = pin;
		return;
	}

	if (status && pin == skipButtonRelease) {
		skipButtonRelease = ~0;
		return;
	}

	if (activePluginCount) {
		if (!status) {
			if (pin) {  // Defer encoder until release due to long pressitaita
				pluginStack[activePluginCount - 1]->onKeyDown(pin);
			}
		} else {
			if (!pin) {  // Dispatch deferred encoder press
				pluginStack[activePluginCount - 1]->onKeyDown(pin);
			}
			pluginStack[activePluginCount - 1]->onKeyUp(pin);
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
				pluginStack[activePluginCount - 1]->onEncoderUp(count);
			} else {
				pluginStack[activePluginCount - 1]->onEncoderDown(count);
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
	display.getTextBounds(pluginStack[activePluginCount - 1]->getDisplayName(), 0, 0, &x, &y, &w, &h);

	display.setCursor(64 - w / 2, 0);
	display.print(pluginStack[activePluginCount - 1]->getDisplayName());
}

void activatePlugin(Plugin* plugin) {
	encoderCount = 0;

	suspendPlugin();

	pluginStack[activePluginCount] = plugin;
	++activePluginCount;

	plugin->onActivate();
	if (!idle && !suspended) {
		plugin->onResume();
		display.clearDisplay();
		drawPluginName();
		display.display();
	}
}

void suspendPlugin() {
	if (activePluginCount && !idle && !suspended) {
		pluginStack[activePluginCount - 1]->onSuspend();
	}
}

void resumePlugin() {
	if (activePluginCount && !idle && !suspended) {
		pluginStack[activePluginCount - 1]->onResume();

		display.clearDisplay();
		drawPluginName();
		display.display();
	}
}

void deactivatePlugin() {
	if (!activePluginCount) {
		return;
	}

	if (!idle && !suspended) {
		pluginStack[activePluginCount - 1]->onSuspend();
	}
	pluginStack[activePluginCount-- - 1]->onDeactivate();

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

	digitalWrite(LED_PIN, LOW);

	populateAppsScreen();

	// Plugin initialization
	if (tud_ready() && pluginCount) {
		activatePlugin(plugins[0]);
	}
}

void loop() {
	// Tick the plugin
	if (activePluginCount) {
		pluginStack[activePluginCount - 1]->onTick();
	}

	// Dispatch keys
	if (!dispatched && (dispatchQueue[0] || dispatchConsumer)) {
		for (uint8_t i {0}; i < 8 && dispatchQueue[i]; ++i) {
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
			return;
		}

		if (activePluginCount > 1) {
			deactivatePlugin();
		} else {
			activatePlugin(mainScreen);
		}
	}

	// Screen timeout
	auto screenTimeout {settingsProvider::getSettings().screenTimeout};
	if (!idle && millis() - lastAction > screenTimeout) {
		suspendPlugin();
		idle = true;
		display.fillScreen(SH110X_BLACK);
		display.display();
		for (uint8_t i {0}; i < 12; ++i) {
			strip.setPixelColor(i, 0);
		}
		strip.show();
	} else if (idle && millis() - lastAction < screenTimeout) {
		idle = false;
		resumePlugin();
	}

	settingsProvider::commitSettings();

	// Update display
	if (updateDisplay) {
		updateDisplay = false;
		display
		    .drawBitmap(0, 8, const_cast<const uint8_t*>(canvasProvider.getBuffer()), 128, 56, SH110X_WHITE, SH110X_BLACK);
		display.display();
	}

	// Update backlight
	if (showBacklight) {
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

		for (uint8_t i {0}; i < 12; ++i) {
			strip.setPixelColor(i, 0);
		}
		strip.show();
	} else if (tud_ready() && suspended) {
		suspended = false;
		resumePlugin();
		lastAction = millis();
	}

	// Serial commands
	if (Serial.available()) {
		auto byte {Serial.read()};
		serialBuffer[serialIdx++] = byte;

		if (!byte || byte == '\r' || (byte == '\n' && serialIdx > 1)) {
			if (!strncmp(serialBuffer, "a>", 2)) {
				uint8_t foundIdx {0};

				for (uint8_t i {0}; i < pluginCount; ++i) {
					if (!strncmp(serialBuffer + 2, plugins[i]->getName(), strlen(plugins[i]->getName()))) {
						foundIdx = i;
						break;
					}
				}

				auto activeName {pluginStack[0]->getName()};
				if (strncmp(activeName, plugins[foundIdx]->getName(), strlen(activeName)) && activePluginCount == 1) {
					deactivatePlugin();
					activatePlugin(plugins[foundIdx]);
					Serial.print("a=");
					Serial.println(plugins[foundIdx]->getName());
				} else {
					Serial.print("a~");
					Serial.println(activeName);
				}
			}

			serialIdx = 0;
		}

		serialIdx = serialIdx % sizeof(serialBuffer);
	}

	delay(1);
}
