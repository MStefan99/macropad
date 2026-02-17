#ifndef PLUGIN_CANVAS_HPP
#define PLUGIN_CANVAS_HPP

#include "Adafruit_GFX.h"
#include "Arduino.h"

class PluginCanvas: public GFXcanvas1 {
public:
	using CallbackType = void (*)();

protected:
	CallbackType _drawCallback {};

public:
	PluginCanvas(CallbackType drawCallback = nullptr);

	void draw();
};

#endif
