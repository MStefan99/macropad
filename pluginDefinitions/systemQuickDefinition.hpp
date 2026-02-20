#ifndef SYSTEM_QUICK_DEFINITION_HPP
#define SYSTEM_QUICK_DEFINITION_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


QuickPlugin::Definition systemQuickDefinition {
  "sys",
  "Desktop",
  {
    {"Files", {KEY_LEFT_GUI, 'e'}, Color::Yellow()},
    },
  {"Volume", {{{}, KEY_VOLUME_DECREMENT}, {{}, KEY_VOLUME_INCREMENT}}}
};

#endif
