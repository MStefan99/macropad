#include "Arduino.h"


constexpr static uint32_t debounceTime {20};

uint32_t buttonTimes[15] {0};


void buttonHandler(void* pinPtr) {
  uint8_t pin {static_cast<uint8_t>(reinterpret_cast<int>(pinPtr))};

  auto buttonTime = buttonTimes[pin];
  buttonTimes[pin] = millis();

  if (millis() - buttonTime < debounceTime) {
    return;
  }

  Serial.print("Button ");
  Serial.println(static_cast<int>(pin));
}

void encoderHandler(void* pinPtr) {
  uint8_t pin {static_cast<uint8_t>(reinterpret_cast<int>(pinPtr) - 17)};

  auto buttonTime = buttonTimes[pin];
  buttonTimes[pin] = millis();

  if (millis() - buttonTime < debounceTime) {
    return;
  }

  Serial.print("Encoder ");
  Serial.println(static_cast<int>(pin));
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