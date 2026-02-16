void buttonHandler(void* pin) {
  Serial.print("Interrupt ");
  Serial.println(reinterpret_cast<int>(pin));
}

void encoderHandler(void* pin) {
  Serial.print("Interrupt ");
  Serial.println(reinterpret_cast<int>(pin));
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