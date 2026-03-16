#ifndef BRIGHTNESS_SCREEN_DEFINITION_HPP
#define BRIGHTNESS_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../Navigator.hpp"
#include "../SettingsProvider.hpp"
#include "../ValueScreen.hpp"


ValueScreen::Definition brightnessScreenDefinition {
  "s_bl",
  "Brightness",
  "Light",
  {0, 31, 1},
  []() -> int {
	return settingsProvider::getSettings().brightness;
    },
  [](int value) {
	auto settings {settingsProvider::getSettings()};
	settings.brightness = value;
	settingsProvider::setSettings(settings);
	pluginEnvironment.backlight.show();
    },
  icons::sun
};

#endif
