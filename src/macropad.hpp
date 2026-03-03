#ifndef MACROPAD_HPP
#define MACROPAD_HPP

#define ALLOW_STORAGE
#define ALLOW_HARDWARE

#include "Adafruit_GFX.h"
#include "Adafruit_NeoPixel.h"
#include "Adafruit_SH110X.h"
#include "Arduino.h"
#include "EEPROM.h"
#include "Keyboard.h"
#include "SPI.h"
#include "tusb.h"

#include "BacklightProvider.hpp"
#include "CanvasProvider.hpp"
#include "icons.hpp"
#include "KeyDispatcher.hpp"
#include "Navigator.hpp"
#include "Plugin.hpp"
#include "PluginEnvironment.hpp"
#include "plugins.hpp"
#include "screens.hpp"
#include "SettingsProvider.hpp"


extern CanvasProvider    canvasProvider;
extern BacklightProvider backlightProvider;
extern KeyDispatcher     keyDispatcher;
extern PluginEnvironment pluginEnvironment;

template <typename T>
int sign(T val) {
	return (T(0) < val) - (val < T(0));
}


#endif
