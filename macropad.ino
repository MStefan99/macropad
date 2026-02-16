#include "Arduino.h"
#include "Keyboard.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_NeoPixel.h>


#define OLED_MOSI     27
#define OLED_CLK      26
#define OLED_DC       24
#define OLED_CS       22
#define OLED_RST      23

#define LED_PIN 13
#define NEOPIXEL_PIN    19
#define NEOPIXEL_COUNT 12


constexpr static uint32_t buttonDebounceTime {20};
constexpr static uint32_t encoderDebounceTime {5};


constexpr static int8_t encoderTransitions[4][4] {
  { 0, -1,  1,  0},
  { 1,  0,  0, -1},
  {-1,  0,  0,  1},
  { 0,  1, -1,  0}
};

static Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);
static Adafruit_NeoPixel strip(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
static PinStatus pinStatuses[13] {};
static uint8_t encoderPosition {0};
static int32_t encoderCount {0};


void buttonHandler(void* pinPtr) {
  uint8_t pin {static_cast<uint8_t>(reinterpret_cast<int>(pinPtr))};
  auto status = digitalRead(pin);

  if (status == pinStatuses[pin]) {
    return;
  }
  pinStatuses[pin] = status;

  strip.setPixelColor(pin - 1, status? 0 : 0xffffff);

  if (status == PinStatus::LOW) {
    Keyboard.press('a' + pin);
  } else {
    Keyboard.release('a' + pin);
  }
}

void encoderHandler(void* pinPtr) {
  uint8_t newPosition = (static_cast<uint8_t>(digitalRead(17)) << 1) | (static_cast<uint8_t>(digitalRead(18)));
  encoderCount -= encoderTransitions[encoderPosition][newPosition];
  encoderPosition = newPosition;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  for (uint8_t i {}; i < sizeof(pinStatuses) / sizeof(pinStatuses[0]); ++i) {
    pinStatuses[i] = digitalRead(i);
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
  delay(2000);
  display.clearDisplay();
  display.display();

  digitalWrite(LED_PIN, LOW);
}

void loop() {
  strip.show();
  delay(20);
}