#ifndef SYSTEM_QUICK_DEFINITION_HPP
#define SYSTEM_QUICK_DEFINITION_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


QuickPlugin::Definition systemQuickDefinition {
  "sys",
  "Desktop",
  {{"Copy", {KEY_LEFT_CTRL, 'c'}, Color::Green()},
    {"Paste", {KEY_LEFT_CTRL, 'v'}, Color::Mint()},
    {"Cut", {KEY_LEFT_CTRL, 'v'}, Color::Cyan()},
    {"< Trk", {}, Color::Yellow(), KEY_SCAN_PREVIOUS},
    {"Pause", {}, Color::Red(), KEY_PLAY_PAUSE},
    {"Trk >", {}, Color::Green(), KEY_SCAN_NEXT},
    {"< Snap", {KEY_LEFT_GUI, KEY_LEFT_ARROW}, Color::Purple()},
    {"Max", {KEY_LEFT_GUI, KEY_PAGE_UP}, Color::Blue()},
    {"Snap >", {KEY_LEFT_GUI, KEY_RIGHT_ARROW}, Color::Purple()},
    {"Apps", {KEY_LEFT_GUI, KEY_TAB}, Color::Lime()},
    {"Min", {KEY_LEFT_GUI, 'd'}, Color::Orange()},
    {"Paste", {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'v'}}},
  {"Volume", {{{}, KEY_VOLUME_DECREMENT}, {{}, KEY_VOLUME_INCREMENT}}, {{}, {KEY_MUTE}}}
};

#endif
