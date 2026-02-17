#ifndef PLUGIN_CANVAS_HPP
#define PLUGIN_CANVAS_HPP

#include "Adafruit_GFX.h"
#include "Arduino.h"

class PluginCanvas: public GFXcanvas1 {
public:
	using CallbackType = void (*)();

	PluginCanvas(CallbackType displayCallback = nullptr);

	void display();

protected:
	CallbackType _displayCallback {};
};

#endif
