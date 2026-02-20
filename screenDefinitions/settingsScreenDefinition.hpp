#ifndef SETTINGS_SCREEN_DEFINITION_HPP
#define SETTINGS_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../ListScreen.hpp"
#include "../Navigator.hpp"
#include "../screens.hpp"


ListScreen::Definition settingsScreenDefinition {
  "s_set",
  "Setup",
  {
    {"Back",
     [](uint8_t i) {
	navigator.close();
},
     icons::exit},
    {"Light",
     [](uint8_t i) {
	navigator.open(brightnessScreen);
},
     icons::sun},
    {"Knob",
     [](uint8_t i) {
	navigator.open(speedScreen);
},
     icons::rotate},
    {"Sound",
     [](uint8_t i) {
	navigator.open(soundScreen);
},
     icons::bell},
    {"Time",
     [](uint8_t i) {
	navigator.open(timeoutScreen);
},
     icons::hourglass},
    },
  1
};

#endif
