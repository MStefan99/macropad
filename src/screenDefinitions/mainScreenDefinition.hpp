#ifndef MAIN_SCREEN_DEFINITION_HPP
#define MAIN_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../ListScreen.hpp"
#include "../Navigator.hpp"
#include "../screens.hpp"


ListScreen::Definition mainScreenDefinition {
  "s_main",
  "Menu",
  "Menu",
  {{"Quit",
    [](uint8_t i) {
	navigator.close();
},
    icons::exit},
    {"Apps",
    [](uint8_t i) {
	navigator.open(appsScreen);
},
    icons::app},
    {"Setup",
    [](uint8_t i) {
	navigator.open(settingsScreen);
},
    icons::cog}},
  1
};

#endif
