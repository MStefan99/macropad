#ifndef KRITA_COMBO_DEFINITION_HPP
#define KRITA_COMBO_DEFINITION_HPP

#include "Keyboard.h"

#include "../ComboPlugin.hpp"


ComboPlugin::Definition kritaComboDefinition {
  "krita",
  "Krita",
  // Keys
  {
   {"Undo", {KEY_LEFT_CTRL, 'z'}, Color::HSV(0)},
   {"Redo", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}, Color::HSV(512)},
   },
  // Layers
  {
   // Tools layer
    {"Brush",
     {
       {},
       {"Erase", {'e'}, Color::Orange()},
       {"0", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '0'}, Color::White()},
       {"1", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '1'}, Color::White()},
       {"2", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '2'}, Color::White()},
       {"3", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '3'}, Color::White()},
       {"4", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '4'}, Color::White()},
       {"5", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '5'}, Color::White()},
       {"6", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '6'}, Color::White()},
       {"7", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '7'}, Color::White()},
       {"8", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '8'}, Color::White()},
       {"9", {KEY_LEFT_CTRL, KEY_LEFT_ALT, '9'}, Color::White()},
     },
     Color::Orange()},
   // (Krita) Layers layer
    {
      "Layer",
      {{"New", {KEY_INSERT}, Color::Green()}, {}, {"Del", {KEY_LEFT_SHIFT, KEY_DELETE}, Color::Red()}},
    },  // Select layer
    {"Select"},
   },
  // Encoder modes
  {{"Brush", {{'['}, {']'}}, Color::Green()},
   {"Zoom", {{'-'}, {'='}}, Color::Yellow()},
   {"History", {{KEY_LEFT_CTRL, 'z'}, {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}}, Color::Orange()}}
};

#endif
