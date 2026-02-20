#ifndef PLUGIN_ENVIRONMENT_HPP
#define PLUGIN_ENVIRONMENT_HPP


#include "Arduino.h"

#include "BacklightProvider.hpp"
#include "CanvasProvider.hpp"
#include "KeyDispatcher.hpp"

struct PluginEnvironment {
	CanvasProvider&    canvas;
	BacklightProvider& backlight;
	KeyDispatcher&     keyDispatcher;

	PluginEnvironment(CanvasProvider& canvas, BacklightProvider& backlight, KeyDispatcher& keyDispatcher):
	  canvas {canvas},
	  backlight {backlight},
	  keyDispatcher {keyDispatcher} {
		// Nothing to do
	}
};


#endif
