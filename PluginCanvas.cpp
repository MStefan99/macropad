#include "PluginCanvas.hpp"

PluginCanvas::PluginCanvas(CallbackType drawCallback):
  GFXcanvas1(128, 56),
  _drawCallback {drawCallback} {
	// Nothing to do
}

void PluginCanvas::draw() {
	if (_drawCallback) {
		_drawCallback();
	}
}
