#ifndef KRITA_DEFINITION_HPP
#define KRITA_DEFINITION_HPP

#include "Keyboard.h"

#include "../ComboPlugin.hpp"
#include "../PluginRegistrar.hpp"

// This plugin uses a custom Krita keymap for additional shortcuts that are missing by default
// Krita keymap file can be found in the resources folder
// It can be imported in Krita by navigating to:
// Settings -> Configure Krita -> Keyboard shortcuts -> Save/Load -> Import scheme


PROGMEM const uint32_t krita_icon[] = {0x00000000, 0x00000000, 0x00f00fe0, 0x00fc3f90, 0x000ff08c, 0x80038047,
                                       0xc001c061, 0x60006030, 0x70003018, 0x30001c0c, 0x1800061e, 0x1800031b,
                                       0x0c808131, 0x0cc0c030, 0x0c406030, 0x0ce03030, 0x0cf01830, 0x0cfc0f30,
                                       0x0c7e0030, 0x0c330030, 0x18110018, 0x18110018, 0x3009000c, 0x700a000e,
                                       0x60040006, 0xc0018003, 0x8003c001, 0x000ff000, 0x00fc3f00, 0x00f00f00,
                                       0x00000000, 0x00000000};


ComboPlugin::Definition kritaDefinition {
  "krita",
  "Krita",
  "Krita",
  // Keys
  {{"Undo", {KEY_LEFT_CTRL, 'z'}, Color::Red()},
   {"Redo", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}, Color::Green()},
   {"Brush", {'b'}, Color::Yellow()},
   {"Save", {KEY_LEFT_CTRL, 's'}, Color::Green()},
   {"Move", {KEY_LEFT_CTRL, 't'}, Color::Azure()},
   {"Lasso", {'s'}, Color::Lime()},
   {"Mirror", {'m'}, Color::Blue()},
   {"InvS", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'i'}, Color::Orange()},
   {"Desel", {KEY_LEFT_CTRL, 'd'}, Color::Magenta()},
   {"SelD", {KEY_LEFT_CTRL, 'h'}, Color::Mint()},
   {"Alpha", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'a'}, Color::Yellow()}},
  // Layers
  {// Brush layer
   {"Brush",
    {
      {},
      {"Erase", {'e'}, Color::Orange()},
      {"0", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '0'}, Color::Green()},
      {"1", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '1'}, Color::Green()},
      {"2", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '2'}, Color::Green()},
      {"3", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '3'}, Color::Green()},
      {"4", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '4'}, Color::Green()},
      {"5", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '5'}, Color::Green()},
      {"6", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '6'}, Color::Green()},
      {"7", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '7'}, Color::Green()},
      {"8", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '8'}, Color::Green()},
      {"9", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '9'}, Color::Green()},
    },
    Color::Yellow()},
   // (Krita) Layers layer
   {"Layer",
    {{"Ins", {KEY_INSERT}, Color::Green()},
     {},
     {"Del", {KEY_LEFT_SHIFT, KEY_DELETE}, Color::Red()},
     {"Group", {KEY_LEFT_CTRL, 'g'}, Color::Cyan()},
     {"Ungr", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'g'}, Color::Magenta()},
     {"Merge", {KEY_LEFT_CTRL, 'e'}, Color::Red()},
     {"Copy+", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'j'}, Color::Lime()},
     {"Cut+", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'j'}, Color::Orange()},
     {"Dupl", {KEY_LEFT_CTRL, 'j'}, Color::Blue()},
     {"Filt+", {KEY_LEFT_SHIFT, 'f'}, Color::Purple()},
     {"FilM+", {KEY_LEFT_SHIFT, 'm'}, Color::Magenta()},
     {"Flat", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'e'}, Color::Red()}},
    Color::Cyan()},
   // Tools layer
   {"Tool",
    {
      {"Asst", {'a'}, Color::Purple()},
      {"Fill", {'f'}, Color::Pink()},
      {},
      {"WandC", {KEY_LEFT_ALT, 'c'}, Color::Azure()},
      {"Wand", {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'w'}, Color::Blue()},
      {"Mag", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'm'}, Color::Purple()},
      {"Line", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'l'}, Color::Orange()},
      {"Ell", {KEY_LEFT_SHIFT, 'j'}, Color::Yellow()},
      {"Poly", {KEY_LEFT_SHIFT, 'r'}, Color::Lime()},
    },
    Color::Lime()},
   {"Filter",
    {
      {"Inv", {KEY_LEFT_CTRL, 'i'}, Color::Red()},
      {"Curve", {KEY_LEFT_CTRL, 'm'}, Color::Azure()},
      {"CCC", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'm'}, Color::Blue()},
      {},
      {"SOP", {KEY_LEFT_CTRL, KEY_LEFT_ALT, ','}, Color::Lime()},
      {"Map", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '.'}, Color::Green()},
      {"Desat", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'u'}, Color::White()},
      {"HSV", {KEY_LEFT_CTRL, 'u'}, Color::Green()},
      {"BlurL", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'b'}, Color::Azure()},
      {"BlurM", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'n'}, Color::Blue()},
      {"Level", {KEY_LEFT_CTRL, 'l'}, Color::Yellow()},
    },
    Color::Purple()},
   {"Blend",
    {{"Mult", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'm'}, Color::Blue(96)},
     {"HardL", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'h'}, Color::Green(96)},
     {"Screen", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 's'}, Color::Yellow(96)},
     {"Norm", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'n'}, Color::Green()},
     {},
     {"Hue", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'u'}, Color::Red()},
     {"LinB", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'a'}, Color::Blue(160)},
     {"LinL", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'j'}, Color::Green(160)},
     {"LinD", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'w'}, Color::Yellow(160)},
     {"Burn", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'b'}, Color::Blue()},
     {"VivL", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'v'}, Color::Green()},
     {"Dodge", {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'd'}, Color::Yellow()}},
    Color::Orange()}
  },
  // Encoder modes
  {
   {"Zoom", {{'-'}, {'='}}, Color::Mint()},
   {"Rot", {{KEY_LEFT_CTRL, '['}, {KEY_LEFT_CTRL, ']'}}, Color::Green()},
   {"Hist", {{KEY_LEFT_CTRL, 'z'}, {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}}, Color::Red()},
   {"Size", {{'['}, {']'}}, Color::Green()},
   {"Flow", {{KEY_LEFT_SHIFT, ','}, {KEY_LEFT_SHIFT, '.'}}, Color::Mint()},
   {"Opct", {{'i'}, {'o'}}, Color::Cyan()},
   {"Hue", {{KEY_LEFT_ALT, ';'}, {KEY_LEFT_ALT, '\''}}, Color::Orange()},
   {"Sat", {{KEY_LEFT_SHIFT, ';'}, {KEY_LEFT_SHIFT, '\''}}, Color::Azure()},
   {"Val", {{'k'}, {'l'}}, Color::White()},
   },
  krita_icon
};


ComboPlugin     kritaPlugin {pluginEnvironment, kritaDefinition};
PluginRegistrar kritaRegistrar {kritaPlugin};

#endif
