#ifndef SYSTEM_QUICK_DEFINITION_HPP
#define SYSTEM_QUICK_DEFINITION_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


PROGMEM const uint32_t desktop_icon[] = {0x00000000, 0xfe1f0000, 0xff3f0000, 0x03300000, 0x03300000, 0xf3330000,
                                         0xf3330000, 0x03f8ff7f, 0x03fcffff, 0x030c00c0, 0x030c00c0, 0x030c00c0,
                                         0x030c00c0, 0x030c00c0, 0x030c00c0, 0x030c00c0, 0x030c00c0, 0x030c00c0,
                                         0x030c00c0, 0x030c00c0, 0x030c00c0, 0xe30d00c0, 0xe3fdffff, 0xe3f9ff7f,
                                         0xe3317800, 0x03307800, 0x03307800, 0x03307800, 0xffbfff07, 0xfe9fff07,
                                         0x00000000, 0x00000000};


QuickPlugin::Definition systemQuickDefinition {
  "sys",
  "Desktop",
  "Desktop",
  {{"Copy", {KEY_LEFT_CTRL, 'c'}, Color::Green()},
    {"Cut", {KEY_LEFT_CTRL, 'x'}, Color::Mint()},
    {"Paste", {KEY_LEFT_CTRL, 'v'}, Color::Cyan()},
    {"< Trk", {{}, KEY_SCAN_PREVIOUS}, Color::Yellow()},
    {"Pause", {{}, KEY_PLAY_PAUSE}, Color::Red()},
    {"Trk >", {{}, KEY_SCAN_NEXT}, Color::Yellow()},
    {"Apps", {KEY_LEFT_GUI, KEY_TAB}, Color::Lime()},
    {"Max", {KEY_LEFT_GUI, KEY_PAGE_UP}, Color::Blue()},
    {"Paste", {KEY_LEFT_GUI, 'v'}, Color::Mint()},
    {"< Snap", {KEY_LEFT_GUI, KEY_LEFT_ARROW}, Color::Purple()},
    {"Min", {KEY_LEFT_GUI, 'd'}, Color::Orange()},
    {"Snap >", {KEY_LEFT_GUI, KEY_RIGHT_ARROW}, Color::Purple()}},
  {"Volume", {{{}, KEY_VOLUME_DECREMENT}, {{}, KEY_VOLUME_INCREMENT}}, {{}, {KEY_MUTE}}},
  desktop_icon
};

#endif
