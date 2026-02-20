#ifndef MAIN_SCREEN_DEFINITION_HPP
#define MAIN_SCREEN_DEFINITION_HPP

#include "Keyboard.h"

#include "../ListScreen.hpp"
#include "../Navigator.hpp"


ListScreen::Definition mainScreenDefinition {
  "s_main",
  "Menu",
  {{"Apps", {[] {
	Serial.println("Apps");
}}},
    {"Setup", {[] {
	Serial.println("Setup");
}}}}
};

#endif
