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
    {"Tool", {{}, {"Brush", {'b'}, Color::Green()}, {"Move", {KEY_LEFT_CTRL, 't'}, Color::Orange()}}, Color::Orange()},
   // (Krita) Layers layer
    {
      "Layer"

    },  // Select layer
    {"Select"},
   },
  // Encoder modes
  {{"Brush", {{'['}, {']'}}, Color::Green()}, {"Zoom"}, {"History"}}
};

#endif
