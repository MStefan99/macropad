#ifndef PLUGIN_CANVAS_HPP
#define PLUGIN_CANVAS_HPP


#include "Adafruit_GFX.h"
#include "Arduino.h"

class CanvasProvider: public GFXcanvas1 {
public:
	using CallbackType = void (*)();

	CanvasProvider(CallbackType displayCallback = nullptr);

	void display();

protected:
	CallbackType _displayCallback {};
};


#endif
