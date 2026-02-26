#ifndef FIREFOX_DEFINITION_HPP
#define FIREFOX_DEFINITION_HPP

#include "Keyboard.h"

#include "../QuickPlugin.hpp"


QuickPlugin::Definition firefoxDefinition {
  "firefox",
  "Firefox",
  {{"Tab -", {KEY_LEFT_CTRL, 'w'}, Color::Red()},
    {"Search", {KEY_LEFT_CTRL, 'k'}, Color::Yellow()},
    {"Tab +", {KEY_LEFT_CTRL, 't'}, Color::Green()},
    {"Top", {KEY_LEFT_CTRL, KEY_UP_ARROW}, Color::Cyan()},
    {"Priv", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'p'}, Color::Red()},
    {"Hist", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'h'}, Color::Mint()},
    {"Reopen", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 't'}, Color::Yellow()},
    {"Downl", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'y'}, Color::Pink()},
    {"Find", {KEY_LEFT_CTRL, 'f'}, Color::Lime()}},
  {"Volume", {{{}, KEY_VOLUME_DECREMENT}, {{}, KEY_VOLUME_INCREMENT}}, {{}, {KEY_PLAY_PAUSE}}}
};

#endif
