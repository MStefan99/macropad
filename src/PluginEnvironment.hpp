#ifndef PLUGIN_ENVIRONMENT_HPP
#define PLUGIN_ENVIRONMENT_HPP


#include "Arduino.h"

#include "BacklightProvider.hpp"
#include "CanvasProvider.hpp"
#include "KeyDispatcher.hpp"
#include "SerialProvider.hpp"

struct PluginEnvironment {
	CanvasProvider&    canvas;
	BacklightProvider& backlight;
	SerialProvider&    serial;
	KeyDispatcher&     keyDispatcher;

	PluginEnvironment(
	    CanvasProvider&    canvas,
	    BacklightProvider& backlight,
	    SerialProvider&    serialProvider,
	    KeyDispatcher&     keyDispatcher
	):
	  canvas {canvas},
	  backlight {backlight},
	  serial {serialProvider},
	  keyDispatcher {keyDispatcher} {
		// Nothing to do
	}
};


#endif
