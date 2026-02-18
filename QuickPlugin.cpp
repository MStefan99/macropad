#include "QuickPlugin.hpp"

QuickPlugin::QuickPlugin(PluginEnvironment& environment, const QuickPluginDefinition& definition):
  Plugin {},
  _environment {environment},
  _definition {definition} {
	Keyboard.begin();
	// Nothing to do
}

void QuickPlugin::onActivate() {
	_environment.canvas.setTextColor(SH110X_WHITE);

	for (uint8_t i {0}; i < 4; ++i) {
		int16_t  x, y;
		uint16_t w, h;

		_environment.canvas.getTextBounds(_definition.keyDefinitions[3 * i].displayName, 0, 0, &x, &y, &w, &h);
		_environment.canvas.setCursor(0, 16 + h * i);
		_environment.canvas.print(_definition.keyDefinitions[3 * i].displayName);

		_environment.canvas.getTextBounds(_definition.keyDefinitions[3 * i + 1].displayName, 0, 0, &x, &y, &w, &h);
		_environment.canvas.setCursor((_environment.canvas.width() - w) / 2, 16 + h * i);
		_environment.canvas.print(_definition.keyDefinitions[3 * i + 1].displayName);

		_environment.canvas.getTextBounds(_definition.keyDefinitions[3 * i + 2].displayName, 0, 0, &x, &y, &w, &h);
		_environment.canvas.setCursor(_environment.canvas.width() - w, 16 + h * i);
		_environment.canvas.print(_definition.keyDefinitions[3 * i + 2].displayName);
	}

	_environment.canvas.display();
}

void QuickPlugin::_highlight(uint8_t key, bool down) {
	int16_t  x, y;
	uint16_t w, h;
	_environment.canvas.getTextBounds(_definition.keyDefinitions[key].displayName, 0, 0, &x, &y, &w, &h);

	switch (key % 3) {
		case 0:
			x = 0;
			break;
		case 1:
			x = (_environment.canvas.width() - w) / 2;
			break;
		case 2:
			x = _environment.canvas.width() - w;
	}
	y = 16 + key / 3 * h;

	_environment.canvas.fillRect(x, y, w, h, down ? SH110X_WHITE : SH110X_BLACK);
	_environment.canvas.setTextColor(down ? SH110X_BLACK : SH110X_WHITE);
	_environment.canvas.setCursor(x, y);
	_environment.canvas.print(_definition.keyDefinitions[key].displayName);
	_environment.canvas.display();
}

void QuickPlugin::onKeyDown(uint8_t key) {
	if (!key) {  // Encoder pressed
		return;
	}
	--key;

	_highlight(key, true);

	_environment.keyDispatcher.dispatch(_definition.keyDefinitions[key].keys);
}

void QuickPlugin::onKeyUp(uint8_t key) {
	if (!key) {  // Encoder pressed
		return;
	}
	--key;

	_highlight(key, false);
}

void QuickPlugin::onEncoderDown(int32_t count) {
	_environment.keyDispatcher.dispatch(_definition.encoderDefinitions[0].keys);
}

void QuickPlugin::onEncoderUp(int32_t count) {
	_environment.keyDispatcher.dispatch(_definition.encoderDefinitions[1].keys);
}

const char* QuickPlugin::getName() const {
	return _definition.displayName;
}
