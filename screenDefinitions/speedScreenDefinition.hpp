#ifndef SPEED_SCREEN_DEFINITION_HPP
#define SPEED_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../Navigator.hpp"
#include "../SelectScreen.hpp"
#include "../SettingsProvider.hpp"


SelectScreen::Definition speedScreenDefinition {
  "s_timeout",
  "Speed",
  {{"x0.25", 16}, {"x0.5", 8}, {"x1", 4}, {"x2", 2}, {"x4", 1}},
  []() -> int {
	return settingsProvider::getSettings().encoderDivisor;
    },
  [](int value) {
	Serial.println("Set time");
	auto settings {settingsProvider::getSettings()};
	settings.encoderDivisor = value;
	settingsProvider::setSettings(settings);
    },
  icons::rotate
};

#endif
