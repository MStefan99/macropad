#include "macropad.hpp"

#define OLED_MOSI 27
#define OLED_CLK  26
#define OLED_DC   24
#define OLED_CS   22
#define OLED_RST  23

#define LED_PIN        13
#define NEOPIXEL_PIN   19
#define NEOPIXEL_COUNT 12


constexpr static uint32_t encoderDebounceTime {2};


constexpr static int8_t encoderTransitions[4][4] {
  {0,  -1, 1,  0 },
  {1,  0,  0,  -1},
  {-1, 0,  0,  1 },
  {0,  1,  -1, 0 }
};
constexpr static uint8_t brightnessTable[32] = {0,   0,   1,   2,   4,   6,   9,   13,  16,  21,  26,
                                                32,  38,  44,  52,  59,  67,  76,  85,  95,  106, 117,
                                                128, 140, 152, 165, 179, 193, 208, 223, 238, 255};

struct __attribute__((packed)) Settings {
	int8_t brightness {31};
};

static Adafruit_SH1106G  display = Adafruit_SH1106G(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);
static Adafruit_NeoPixel strip(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

static Settings settings {};

static PinStatus pinStatuses[13] {};
static uint8_t   encoderPosition {0};
static int32_t   encoderCount {0};
static uint32_t  encoderTime {0};

static Plugin* activePlugin {nullptr};

const static uint16_t* dispatchQueue {nullptr};
static bool            dispatched {false};
static uint32_t        dispatchStart {0};
static uint32_t        dispatchDuration {0};
static bool            dispatchConsumer {false};

void displayPlugin() {
	display.drawBitmap(0, 8, const_cast<const uint8_t*>(pluginCanvas.getBuffer()), 128, 56, SH110X_WHITE, SH110X_BLACK);
	display.display();
}

void setBacklight() {
	for (uint8_t i {0}; i < 12; ++i) {
		auto color {pluginBacklight.getPixel(i)};
		strip.setPixelColor(
		    i,
		    (color.getR() * brightnessTable[settings.brightness]) >> 8u,
		    (color.getG() * brightnessTable[settings.brightness]) >> 8u,
		    (color.getB() * brightnessTable[settings.brightness]) >> 8u
		);
	}

	strip.show();
}

void dispatchKeys(const uint16_t keys[6], bool consumerKeys, uint32_t duration) {
	dispatchQueue = keys;
	dispatchDuration = duration;
	dispatchConsumer = consumerKeys;
}

PluginCanvas    pluginCanvas {displayPlugin};
PluginBacklight pluginBacklight {setBacklight};
PluginTone      pluginTone {};
KeyDispatcher   keyDispatcher {dispatchKeys};


PluginEnvironment pluginEnvironment {pluginCanvas, pluginBacklight, pluginTone, keyDispatcher};

void buttonHandler(void* pinPtr) {
	uint8_t pin {static_cast<uint8_t>(reinterpret_cast<int>(pinPtr))};
	auto    status = digitalRead(pin);

	if (status == pinStatuses[pin]) {
		return;
	}
	pinStatuses[pin] = status;

	if (activePlugin) {
		if (status) {
			activePlugin->onKeyUp(pin);
		} else {
			activePlugin->onKeyDown(pin);
		}
	}
}

void encoderHandler(void* pinPtr) {
	uint8_t newPosition = (static_cast<uint8_t>(digitalRead(17)) << 1) | (static_cast<uint8_t>(digitalRead(18)));
	int8_t  transition = -encoderTransitions[encoderPosition][newPosition];
	encoderCount += transition;
	encoderPosition = newPosition;

	auto lastEncoderTime {encoderTime};
	encoderTime = millis();

	if (millis() - lastEncoderTime < encoderDebounceTime) {
		return;
	}

	if (transition && !(encoderCount % 4)) {
		if (!pinStatuses[0]) {  // Setting brightness
			settings.brightness = min(max(settings.brightness + transition, 0), 31);
			setBacklight();
			EEPROM.put(0, settings);
			EEPROM.commit();
		} else if (activePlugin) {
			if (transition > 0) {
				activePlugin->onEncoderUp(encoderCount);
			} else {
				activePlugin->onEncoderDown(encoderCount);
			}
		}
	}
}

void enablePlugin(Plugin* plugin) {
	if (activePlugin) {
		activePlugin->onDeactivate();
	}

	encoderCount = 0;
	plugin->onActivate();
	activePlugin = plugin;

	int16_t  x, y;
	uint16_t w, h;
	display.getTextBounds(activePlugin->getName(), 0, 0, &x, &y, &w, &h);

	display.setCursor(64 - w / 2, 0);
	display.print(activePlugin->getName());

	display.display();
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
	display.clearDisplay();
	display.fillRect(0, 0, 128, 8, SH110X_WHITE);
	display.setTextColor(SH110X_BLACK);

	EEPROM.begin(256);
	EEPROM.get(0, settings);

	digitalWrite(LED_PIN, LOW);

	// Plugin initialization
	if (definedPlugins[0]) {  // TODO: Bad, needs fixing
		enablePlugin(definedPlugins[0]);
	}
}

uint16_t h {0};

void loop() {
	if (activePlugin) {
		activePlugin->onTick();
	}

	if (dispatchQueue) {
		for (uint8_t i {0}; i < 6 && dispatchQueue[i]; ++i) {
			if (dispatchConsumer) {
				Keyboard.consumerPress(dispatchQueue[i]);
			} else {
				Keyboard.press(dispatchQueue[i]);
			}
		}

		dispatchQueue = nullptr;
		dispatchStart = millis();
		dispatched = true;
	}

	if (dispatched && millis() - dispatchStart > dispatchDuration) {
		Keyboard.releaseAll();
		dispatched = false;
	}

	strip.show();

	delay(10);
}
