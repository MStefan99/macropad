#include "CanvasProvider.hpp"

CanvasProvider::CanvasProvider(CallbackType displayCallback):
  GFXcanvas1(128, 56),
  _displayCallback {displayCallback} {
	// Nothing to do
}

void CanvasProvider::display() {
	if (_displayCallback) {
		_displayCallback();
	}
}
