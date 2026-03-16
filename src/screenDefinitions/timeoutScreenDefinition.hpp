#ifndef TIMEOUT_SCREEN_DEFINITION_HPP
#define TIMEOUT_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../Navigator.hpp"
#include "../SelectScreen.hpp"
#include "../SettingsProvider.hpp"


SelectScreen::Definition timeoutScreenDefinition {
  "s_timeout",
  "Screen timeout",
  "Timeout",
  {{"15s", 1000 * 15},
    {"30s", 1000 * 30},
    {"1m", 1000 * 60},
    {"3m", 1000 * 60 * 3},
    {"5m", 1000 * 60 * 5},
    {"10m", 1000 * 60 * 10},
    {"30m", 1000 * 60 * 30},
    {"1h", 1000 * 60 * 60}},
  []() -> int {
	return settingsProvider::getSettings().screenTimeout;
    },
  [](int value) {
	auto settings {settingsProvider::getSettings()};
	settings.screenTimeout = value;
	settingsProvider::setSettings(settings);
    },
  icons::hourglass
};

#endif
