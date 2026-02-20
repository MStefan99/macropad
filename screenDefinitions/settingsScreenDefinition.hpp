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
     [] {
	navigator.close();
},
     icons::exit},
    {"Light",
     [] {
	navigator.open(brightnessScreen);
},
     icons::sun},
    {"Knob",
     [] {
	navigator.open(speedScreen);
},
     icons::rotate},
    {"Sound",
     [] {
	navigator.open(soundScreen);
},
     icons::bell},
    {"Time",
     [] {
	navigator.open(timeoutScreen);
},
     icons::hourglass},
    },
  1
};

#endif
