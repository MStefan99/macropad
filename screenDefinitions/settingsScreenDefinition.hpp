#ifndef SETTINGS_SCREEN_DEFINITION_HPP
#define SETTINGS_SCREEN_DEFINITION_HPP

#include "Keyboard.h"

#include "../ListScreen.hpp"
#include "../Navigator.hpp"


ListScreen::Definition settingsScreenDefinition {
  "s_set",
  "Setup",
  {{"Light",
    [] {
	Serial.println("Light");
}},
    {"Time",
    [] {
	Serial.println("Time");
}},
    {"Knob",
    [] {
	Serial.println("Knob");
}},
    {"Sound", [] {
	Serial.println("Sound");
}}}
};

#endif
