#ifndef TIMEOUT_SCREEN_DEFINITION_HPP
#define TIMEOUT_SCREEN_DEFINITION_HPP

#include "Keyboard.h"

#include "../icons.hpp"
#include "../Navigator.hpp"
#include "../SelectScreen.hpp"
#include "../SettingsProvider.hpp"


SelectScreen::Definition timeoutScreenDefinition {
  "s_timeout",
  "Timeout",
  "Timeout",
  {{"10s", 1000 * 10},
    {"30s", 1000 * 30},
    {"1m", 1000 * 60},
    {"5m", 1000 * 60 * 5},
    {"10m", 1000 * 60 * 10},
    {"30m", 1000 * 60 * 30}},
  []() -> int {
	return settingsProvider::getSettings().screenTimeout;
    },
  [](int value) {
	Serial.println("Set time");
	auto settings {settingsProvider::getSettings()};
	settings.screenTimeout = value;
	settingsProvider::setSettings(settings);
    },
  icons::hourglass
};

#endif
