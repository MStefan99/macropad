#ifndef PLUGIN_ENVIRONMENT_HPP
#define PLUGIN_ENVIRONMENT_HPP


#include "Arduino.h"

#include "BacklightProvider.hpp"
#include "CanvasProvider.hpp"
#include "KeyDispatcher.hpp"
#include "ToneProvider.hpp"

struct PluginEnvironment {
	CanvasProvider&    canvas;
	BacklightProvider& backlight;
	ToneProvider&      tone;
	KeyDispatcher&     keyDispatcher;

	PluginEnvironment(
	    CanvasProvider&    canvas,
	    BacklightProvider& backlight,
	    ToneProvider&      tone,
	    KeyDispatcher&     keyDispatcher
	):
	  canvas {canvas},
	  backlight {backlight},
	  tone {tone},
	  keyDispatcher {keyDispatcher} {
		// Nothing to do
	}
};


#endif
