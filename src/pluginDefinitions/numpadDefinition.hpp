#ifndef NUMPAD_DEFINITION_HPP
#define NUMPAD_DEFINITION_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


PROGMEM const uint32_t numpad_icon[] = {0xfeffff7f, 0xffffffff, 0x038001c0, 0x038001c0, 0x838741c0, 0xc38cc1c0,
                                        0x4388c1c1, 0xc380c1c3, 0x8381c1c0, 0x0383c1c0, 0x0386c1c0, 0x038cc1c0,
                                        0xe38ff1c7, 0x038001c0, 0x038001c0, 0xffffffff, 0xffffffff, 0x038001c0,
                                        0x038001c0, 0xc380f1c7, 0xc38131c0, 0xc38361c0, 0xc386e1c1, 0xc38c31c3,
                                        0xc38c11c0, 0xe38f11c0, 0xc38031c4, 0xc380e1c3, 0x038001c0, 0x038001c0,
                                        0xffffffff, 0xfeffff7f};


QuickPlugin::Definition numpadDefinition {
  "numpad",
  "Numpad",
  "Numpad",
  {{"7", {KEY_KP_7}, Color::Blue(80)},
    {"8", {KEY_KP_8}, Color::Blue(80)},
    {"9", {KEY_KP_9}, Color::Blue(80)},
    {"4", {KEY_KP_4}, Color::Blue(80)},
    {"5", {KEY_KP_5}, Color::Blue(80)},
    {"6", {KEY_KP_6}, Color::Blue(80)},
    {"1", {KEY_KP_1}, Color::Blue(80)},
    {"2", {KEY_KP_2}, Color::Blue(80)},
    {"3", {KEY_KP_3}, Color::Blue(80)},
    {"Del", {KEY_BACKSPACE}, Color::Red()},
    {"0", {KEY_KP_0}, Color::Blue(80)},
    {"Enter", {KEY_RETURN}, Color::Green()}},
  {"Volume", {{{}, KEY_VOLUME_DECREMENT}, {{}, KEY_VOLUME_INCREMENT}}, {{}, {KEY_MUTE}}},
  numpad_icon
};

#endif
