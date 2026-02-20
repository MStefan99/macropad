#ifndef SCREEN_ENVIRONMENT_HPP
#define SCREEN_ENVIRONMENT_HPP


#include "Arduino.h"

#include "BacklightProvider.hpp"
#include "CanvasProvider.hpp"
#include "KeyDispatcher.hpp"
#include "Navigator.hpp"
#include "ToneProvider.hpp"

struct ScreenEnvironment: public PluginEnvironment {
	Navigator& navigator;

	ScreenEnvironment(
	    CanvasProvider&    canvas,
	    BacklightProvider& backlight,
	    ToneProvider&      tone,
	    KeyDispatcher&     keyDispatcher,
	    Navigator&         navigator
	):
	  PluginEnvironment {canvas, backlight, tone, keyDispatcher},
	  navigator {navigator} {
		// Nothing to do
	}
};


#endif
