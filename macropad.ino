#include "Arduino.h"


constexpr static uint32_t buttonDebounceTime {20};
constexpr static uint32_t encoderDebounceTime {5};


constexpr static int8_t encoderTransitions[4][4] {
  { 0, -1,  1,  0},
  { 1,  0,  0, -1},
  {-1,  0,  0,  1},
  { 0,  1, -1,  0}
};

static uint32_t buttonTimes[14] {0};
static uint8_t encoderPosition = 0;
static int32_t encoderCount {0};


void buttonHandler(void* pinPtr) {
  uint8_t pin {static_cast<uint8_t>(reinterpret_cast<int>(pinPtr))};

  auto buttonTime = buttonTimes[pin];
  buttonTimes[pin] = millis();

  if (millis() - buttonTime < buttonDebounceTime) {
    return;
  }

  Serial.print("Button ");
  Serial.println(static_cast<int>(pin));
}

void encoderHandler(void* pinPtr) {
  auto buttonTime = buttonTimes[13];
  buttonTimes[13] = millis();

  if (millis() - buttonTime < encoderDebounceTime) {
    return;
  }

  uint8_t newPosition = (static_cast<uint8_t>(digitalRead(17)) << 1) | (static_cast<uint8_t>(digitalRead(18)));
  encoderCount -= encoderTransitions[encoderPosition][newPosition];
  encoderPosition = newPosition;
}

void setup() {
  // Some boards work best if we also make a serial connection
  Serial.begin(115200);

  for (uint8_t i {0}; i <= 12; ++i) {
    pinMode(i, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(i), buttonHandler, PinStatus::CHANGE, reinterpret_cast<void*>(i));
  }

  for (uint8_t i {17}; i <= 18; ++i) {
    pinMode(i, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(i), encoderHandler, PinStatus::CHANGE, reinterpret_cast<void*>(i));
  }
}

void loop() {
  delay(500);
}