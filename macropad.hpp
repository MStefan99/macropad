#ifndef MACROPAD_HPP
#define MACROPAD_HPP

#define ALLOW_HARDWARE

#include "Adafruit_GFX.h"
#include "Adafruit_NeoPixel.h"
#include "Adafruit_SH110X.h"
#include "tusb.h"
#include "Arduino.h"
#include "Keyboard.h"
#include "SPI.h"
#include "EEPROM.h"

#include "KeyDispatcher.hpp"
#include "Plugin.hpp"
#include "PluginBacklight.hpp"
#include "PluginCanvas.hpp"
#include "PluginEnvironment.hpp"
#include "PluginTone.hpp"


extern PluginCanvas      pluginCanvas;
extern PluginBacklight   pluginBacklight;
extern PluginTone        pluginTone;
extern KeyDispatcher     keyDispatcher;
extern PluginEnvironment pluginEnvironment;


extern Plugin* definedPlugins[];


#endif
