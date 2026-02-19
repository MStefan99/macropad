#ifndef SYSTEM_QUICK_DEFINITION_HPP
#define SYSTEM_QUICK_DEFINITION_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


QuickPluginDefinition systemQuickDefinition {
  "sys",
  "Desktop",
  {
    {"Files", {KEY_LEFT_GUI, 'e'}, Color::HSV(256)},
    },
  {"Volume", {{KEY_VOLUME_DECREMENT}, {KEY_VOLUME_INCREMENT}}}
};

#endif
