#ifndef TEST_PLUGIN_HPP
#define TEST_PLUGIN_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


QuickPluginDefinition kritaQuickDefinition {
  "krita",
  "Krita",
  {{"Undo", {KEY_LEFT_CTRL, 'z'}, Color::HSV(0)},
    {"Redo", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}, Color::HSV(512)},
    {"Select", {KEY_LEFT_CTRL, 'a'}, Color::HSV(1024, 180)},
    {"Brush", {'b'}, Color::HSV(512)},
    {"Eraser", {'e'}, Color::HSV(64)},
    {"Desel", {KEY_LEFT_CTRL, 'd'}, Color::HSV(0, 180)},
    {"Layer+", {KEY_INSERT}, Color::HSV(1024, 160)},
    {"Layer-", {KEY_LEFT_SHIFT, KEY_DELETE}, Color::HSV(0, 180)},
    {"Move", {KEY_LEFT_CTRL, 't'}, Color::HSV(1024, 180)},
    {"BG", {KEY_BACKSPACE}, Color::HSV(256)},
    {"FG", {KEY_LEFT_SHIFT, KEY_BACKSPACE}, Color::HSV(128)},
    {"Clear", {KEY_DELETE}, Color::HSV(0)}},
  {"Brush", {{'['}, {']'}}}
};

#endif
