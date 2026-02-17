#ifndef PLUGIN_ENVIRONMENT_HPP
#define PLUGIN_ENVIRONMENT_HPP

#include "Arduino.h"

#include "KeyDispatcher.hpp"
#include "PluginBacklight.hpp"
#include "PluginCanvas.hpp"
#include "PluginTone.hpp"

struct PluginEnvironment {
	PluginCanvas    canvas;
	PluginBacklight backlight;
	PluginTone      tone;
	KeyDispatcher   keyDispatcher;

	PluginEnvironment(
	    const PluginCanvas&    canvas,
	    const PluginBacklight& backlight,
	    const PluginTone&      tone,
	    const KeyDispatcher&   keyDispatcher
	):
	  canvas {canvas},
	  backlight {backlight},
	  tone {tone},
	  keyDispatcher {keyDispatcher} {
		// Nothing to do
	}
};

#endif
