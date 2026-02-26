#ifndef KRITA_DEFINITION_HPP
#define KRITA_DEFINITION_HPP

#include "Keyboard.h"

#include "../ComboPlugin.hpp"


ComboPlugin::Definition kritaDefinition {
  "krita",
  "Krita",
  // Keys
  {{"Undo", {KEY_LEFT_CTRL, 'z'}, Color::Red()},
   {"Redo", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}, Color::Green()},
   {"Brush", {'b'}, Color::Yellow()},
   {"Save", {KEY_LEFT_CTRL, 's'}, Color::Green()},
   {"Move", {KEY_LEFT_CTRL, 't'}, Color::Azure()},
   {"Lasso", {'s'}, Color::Lime()},
   {"Mirror", {'m'}, Color::Blue()},
   {},
   {"Desel", {KEY_LEFT_CTRL, 'd'}, Color::Magenta()}},
  // Layers
  {
   // Brushb layer
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
     {
       {"Ins", {KEY_INSERT}, Color::Green()},
       {},
       {"Del", {KEY_LEFT_SHIFT, KEY_DELETE}, Color::Red()},
       {"Group", {KEY_LEFT_CTRL, 'g'}, Color::Cyan()},
       {"Ungr", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'g'}, Color::Magenta()},
       {"Merge", {KEY_LEFT_CTRL, 'e'}, Color::Red()},
       {"Copy+", {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'j'}, Color::Lime()},
       {"Cut+", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'j'}, Color::Orange()},
       {"Dupl", {KEY_LEFT_CTRL, 'j'}, Color::Blue()},
     },
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
   },
  // Encoder modes
  {
   {"Zoom", {{'-'}, {'='}}, Color::Mint()},
   {"Rot", {{KEY_LEFT_CTRL, '['}, {KEY_LEFT_CTRL, ']'}}, Color::Green()},
   {"Hist", {{KEY_LEFT_CTRL, 'z'}, {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}}, Color::Red()},
   {"Size", {{'['}, {']'}}, Color::Green()},
   {"Flow", {{KEY_LEFT_SHIFT, ','}, {KEY_LEFT_SHIFT, '.'}}, Color::Mint()},
   {"Opct", {{'i'}, {'o'}}, Color::Cyan()},
   {"Layer", {{KEY_PAGE_UP}, {KEY_PAGE_DOWN}}, Color::Yellow()},
   }
};

#endif
