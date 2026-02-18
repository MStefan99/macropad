#ifndef TEST_PLUGIN_HPP
#define TEST_PLUGIN_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


QuickPluginDefinition kritaQuickDefinition {
  "krita",
  "Krita",
  {{"Undo", {KEY_LEFT_CTRL, 'z'}, {0xff0000}},
    {"Redo", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}},
    {"Select", {KEY_LEFT_CTRL, 'a'}},
    {"Brush", {'b'}},
    {"Eraser", {'e'}},
    {"Desel", {KEY_LEFT_CTRL, 'd'}},
    {"Layer+", {KEY_INSERT}},
    {"Layer-", {KEY_LEFT_SHIFT, KEY_DELETE}},
    {"Move", {KEY_LEFT_CTRL, 't'}},
    {"BG", {KEY_BACKSPACE}},
    {"FG", {KEY_LEFT_SHIFT, KEY_BACKSPACE}},
    {"Clear", {KEY_DELETE}}}
};

#endif
