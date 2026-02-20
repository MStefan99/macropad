#ifndef SETTINGS_SCREEN_DEFINITION_HPP
#define SETTINGS_SCREEN_DEFINITION_HPP

#include "Keyboard.h"

#include "../icons.hpp"
#include "../ListScreen.hpp"
#include "../Navigator.hpp"
#include "../screens.hpp"


ListScreen::Definition settingsScreenDefinition {
  "s_set",
  "Setup",
  {
    {"Back",
     [] {
	navigator.close();
},
     icons::exit},
    {"Light",
     [] {
	Serial.println("Light");
},
     icons::sun},
    {"Knob",
     [] {
	Serial.println("Knob");
},
     icons::rotate},
    {"Sound",
     [] {
	navigator.open(soundScreen);
},
     icons::bell},
    {"Time",
     [] {
	Serial.println("Time");
},
     icons::hourglass},
    },
  1
};

#endif
