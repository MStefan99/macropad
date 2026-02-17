#include "PluginCanvas.hpp"

PluginCanvas::PluginCanvas(CallbackType displayCallback):
  GFXcanvas1(128, 56),
  _displayCallback {displayCallback} {
	// Nothing to do
}

void PluginCanvas::display() {
	if (_displayCallback) {
		_displayCallback();
	}
}
