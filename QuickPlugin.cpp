#include "QuickPlugin.hpp"

QuickPlugin::QuickPlugin(PluginEnvironment& environment, const Definition& definition):
  Plugin {environment},
  _definition {definition} {
	// Nothing to do
}

void QuickPlugin::onActivate() {
	for (uint8_t i {0}; i < 12; ++i) {
		_environment.backlight.setPixel(i, _definition.keyDefinitions[i].color);
	}
	_environment.backlight.show();

	_environment.canvas.fillScreen(SH110X_BLACK);
	_environment.canvas.setTextColor(SH110X_WHITE);
	int16_t  x, y;
	uint16_t w, h;

	_environment.canvas.getTextBounds(_definition.encoderDefinition.displayName, 0, 0, &x, &y, &w, &h);
	_environment.canvas.setCursor(_environment.canvas.width() - w - 4, 4);
	_environment.canvas.print(_definition.encoderDefinition.displayName);

	for (uint8_t i {0}; i < 4; ++i) {
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

	auto kd {_definition.keyDefinitions[key]};
	_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
}

void QuickPlugin::onKeyUp(uint8_t key) {
	if (!key) {  // Encoder pressed
		return;
	}
	--key;

	_highlight(key, false);
}

void QuickPlugin::onEncoderDown(int32_t count) {
	auto kd {_definition.encoderDefinition.encoderKeys[0]};
	_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
}

void QuickPlugin::onEncoderUp(int32_t count) {
	auto kd {_definition.encoderDefinition.encoderKeys[1]};
	_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
}

const char* QuickPlugin::getName() const {
	return _definition.name;
}

const char* QuickPlugin::getDisplayName() const {
	return _definition.displayName;
}
