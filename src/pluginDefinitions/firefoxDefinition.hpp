// Make sure to use a unique name here, otherwise your plugin won't show up
#ifndef FIREFOX_DEFINITION_HPP
#define FIREFOX_DEFINITION_HPP

#include "Keyboard.h"

#include "../PluginRegistrar.hpp"
#include "../QuickPlugin.hpp"


// Generate the icon array using the img2array.py
PROGMEM const uint32_t firefox_icon[] = {0x00080000, 0x001c0000, 0x003c0000, 0x007e0000, 0x007f0000, 0x80ff0006,
                                         0xc0ff600e, 0xd0ffe01a, 0xf83fa017, 0xf80fa03b, 0xfc077035, 0xfc1bb86a,
                                         0xf60f6f57, 0xfa07f36f, 0xf607fe57, 0xfa03f06a, 0xf6034055, 0xea03c06a,
                                         0xd603c055, 0xaa07c06a, 0x56076075, 0xae0eb02a, 0x543d5c35, 0xaceaaf1a,
                                         0x5855551d, 0xb0aaaa0e, 0x60555507, 0xc0aaaa03, 0x8057d501, 0x00ae7a00,
                                         0x00f81f00, 0x00000000};


QuickPlugin::Definition firefoxDefinition {
  "firefox", // System name, must match the executable name (i.e. firefox.exe)
  "Firefox", // Display name, visible in the plugin header. 23 characters max
  "Firefox", // Short name, visible in the app list. 7 characters max
  // Shortcuts
  // For available keys, see Keyboard.h
  // Default colors are available in Color.hpp
  {{"Tab -", {KEY_LEFT_CTRL, 'w'}, Color::Red()},
   {"Search", {KEY_LEFT_CTRL, 'k'}, Color::Yellow()},
   {"Tab +", {KEY_LEFT_CTRL, 't'}, Color::Green()},
   {"Top", {KEY_LEFT_CTRL, KEY_UP_ARROW}, Color::Cyan()},
   {"Priv", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'p'}, Color::Purple()},
   {"Reopen", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 't'}, Color::Yellow()},
   {"Hist", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'h'}, Color::Mint()},
   {"Downl", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'y'}, Color::Pink()},
   {"Find", {KEY_LEFT_CTRL, 'f'}, Color::Lime()}},
  // Encoder actions: down, up, push
  // Consumer key must be defined as a second element: {KEY}, CONSUMER_KEY
  {"Volume", {{{}, KEY_VOLUME_DECREMENT}, {{}, KEY_VOLUME_INCREMENT}}, {{}, {KEY_PLAY_PAUSE}}},
  firefox_icon  // Icon defined at the top of the file
};


// Register the plugin so that macropad can find it
QuickPlugin     firefoxPlugin {pluginEnvironment, firefoxDefinition};
PluginRegistrar firefoxRegistrar {firefoxPlugin};


// Don't forget to add the .hpp file to plugins.cpp

#endif
