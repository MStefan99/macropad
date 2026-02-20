#ifndef SOUND_SCREEN_DEFINITION_HPP
#define SOUND_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../Navigator.hpp"
#include "../OptionScreen.hpp"
#include "../SettingsProvider.hpp"


OptionScreen::Definition soundScreenDefinition {"s_sound", "Sound", [] {
	return settingsProvider::getSettings().soundEnabled;
}, [](bool value) {
	auto settings {settingsProvider::getSettings()};
	settings.soundEnabled = value;
	settingsProvider::setSettings(settings);
}, icons::bell};

#endif
