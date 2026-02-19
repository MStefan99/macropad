#include "macropad.hpp"

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


constexpr static int8_t encoderTransitions[4][4] {
  {0,  -1, 1,  0 },
  {1,  0,  0,  -1},
  {-1, 0,  0,  1 },
  {0,  1,  -1, 0 }
};

struct __attribute__((packed)) Settings {
	int8_t brightness {31};
};

static Adafruit_SH1106G  display = Adafruit_SH1106G(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);
static Adafruit_NeoPixel strip(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

static bool updateDisplay {false};
static bool showBacklight {false};
static bool commitSettings {false};

static Settings settings {};

static PinStatus pinStatuses[13] {};
static uint32_t  pinTimes[13] {};
static bool      skipEncoderRelease {false};

static uint8_t  encoderPosition {0};
static int32_t  encoderCount {0};
static uint32_t encoderTime {0};

static Plugin* activePlugin {nullptr};

static uint8_t  dispatchQueue[8] {0};
static uint16_t dispatchConsumer {0};
static bool     dispatched {false};
static uint32_t dispatchStart {0};
static uint32_t dispatchDuration {0};

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
	for (uint8_t i {0}; i < 6 && keys[i]; ++i) {
		dispatchQueue[i] = keys[i];
	}

	dispatchConsumer = consumerKey;
	dispatchDuration = duration;
}

PluginCanvas    pluginCanvas {displayPlugin};
PluginBacklight pluginBacklight {setBacklight};
PluginTone      pluginTone {};
KeyDispatcher   keyDispatcher {dispatchKeys};


PluginEnvironment pluginEnvironment {pluginCanvas, pluginBacklight, pluginTone, keyDispatcher};

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

	if (status && skipEncoderRelease) {
		skipEncoderRelease = false;
		return;
	}

	if (activePlugin) {
		if (status) {
			activePlugin->onKeyUp(pin);
		} else {
			activePlugin->onKeyDown(pin);
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

	if (transition && !(encoderCount % 4)) {
		if (!pinStatuses[0] && tud_ready()) {  // Setting brightness
			settings.brightness = min(max(settings.brightness + transition, 0), 31);
			skipEncoderRelease = true;
			commitSettings = true;
			setBacklight();
		} else if (activePlugin) {
			int32_t count = encoderCount / 4;

			if (transition > 0) {
				activePlugin->onEncoderUp(count);
			} else {
				activePlugin->onEncoderDown(count);
			}
		}
	}
}

void activatePlugin(Plugin* plugin) {
	if (activePlugin) {
		activePlugin->onDeactivate();
	}

	encoderCount = 0;
	plugin->onActivate();
	activePlugin = plugin;

	display.clearDisplay();
	display.fillRect(0, 0, 128, 8, SH110X_WHITE);
	display.setTextColor(SH110X_BLACK);

	int16_t  x, y;
	uint16_t w, h;
	display.getTextBounds(activePlugin->getDisplayName(), 0, 0, &x, &y, &w, &h);

	display.setCursor(64 - w / 2, 0);
	display.print(activePlugin->getDisplayName());

	display.display();
}

void deactivatePlugin() {
	if (!activePlugin) {
		return;
	}

	activePlugin->onDeactivate();
	activePlugin = nullptr;
}

void setup() {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);

	for (uint8_t i {}; i < sizeof(pinStatuses) / sizeof(pinStatuses[0]); ++i) {
		pinStatuses[i] = PinStatus::HIGH;
	}

	for (uint8_t i {0}; i <= 12; ++i) {
		pinMode(i, INPUT_PULLUP);
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
	display.display();
	delay(1000);

	EEPROM.begin(256);
	EEPROM.get(0, settings);

	digitalWrite(LED_PIN, LOW);

	// Plugin initialization
	if (tud_ready() && definedPlugins[0]) {  // TODO: Bad, needs fixing
		activatePlugin(definedPlugins[0]);
	} else {
		display.fillScreen(SH110X_BLACK);
		display.display();
	}
}

void loop() {
	if (activePlugin) {
		activePlugin->onTick();
	}

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

	if (dispatched && millis() - dispatchStart > dispatchDuration) {
		dispatched = false;
		Keyboard.releaseAll();
		Keyboard.consumerRelease();
	}

	if (updateDisplay) {
		updateDisplay = false;
		display.drawBitmap(0, 8, const_cast<const uint8_t*>(pluginCanvas.getBuffer()), 128, 56, SH110X_WHITE, SH110X_BLACK);
		display.display();
	}

	if (commitSettings) {
		commitSettings = false;
		EEPROM.put(0, settings);
		EEPROM.commit();
	}

	if (showBacklight) {
		showBacklight = false;
		uint8_t brightness = settings.brightness * (256 / 32);

		for (uint8_t i {0}; i < 12; ++i) {
			auto color {pluginBacklight.getPixel(i)};
			strip.setPixelColor(
			    i,
			    strip.gamma8((color.getR() * brightness) >> 8u),
			    strip.gamma8((color.getG() * brightness) >> 8u),
			    strip.gamma8((color.getB() * brightness) >> 8u)
			);
		}
		strip.show();
	}

	if (!tud_ready() && activePlugin) {
		deactivatePlugin();
		display.fillScreen(SH110X_BLACK);
		display.display();

		for (uint8_t i {0}; i < 12; ++i) {
			strip.setPixelColor(i, 0);
		}
		strip.show();
	} else if (tud_ready() && !activePlugin && definedPlugins[0]) {
		activatePlugin(definedPlugins[0]);
	}

	delay(1);
}
