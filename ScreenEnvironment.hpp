#ifndef SCREEN_ENVIRONMENT_HPP
#define SCREEN_ENVIRONMENT_HPP


#include "Arduino.h"

#include "KeyDispatcher.hpp"
#include "PluginBacklight.hpp"
#include "PluginCanvas.hpp"
#include "PluginTone.hpp"

struct PluginEnvironment {
	PluginCanvas&    canvas;
	PluginBacklight& backlight;
	PluginTone&      tone;
	KeyDispatcher&   keyDispatcher;

	PluginEnvironment(PluginCanvas& canvas, PluginBacklight& backlight, PluginTone& tone, KeyDispatcher& keyDispatcher):
	  canvas {canvas},
	  backlight {backlight},
	  tone {tone},
	  keyDispatcher {keyDispatcher} {
		// Nothing to do
	}
};


#endif
