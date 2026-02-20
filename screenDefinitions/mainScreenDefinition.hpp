#ifndef MAIN_SCREEN_DEFINITION_HPP
#define MAIN_SCREEN_DEFINITION_HPP

#include "../icons.hpp"
#include "../ListScreen.hpp"
#include "../Navigator.hpp"
#include "../screens.hpp"


ListScreen::Definition mainScreenDefinition {
  "s_main",
  "Menu",
  {{"Quit",
    [] {
	navigator.close();
},
    icons::exit},
    {"Apps",
    [] {
	Serial.println("Apps");
},
    icons::app},
    {"Setup",
    [] {
	navigator.open(settingsScreen);
},
    icons::cog}},
  1
};

#endif
