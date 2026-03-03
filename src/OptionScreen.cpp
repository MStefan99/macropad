#include "OptionScreen.hpp"

OptionScreen::OptionScreen(PluginEnvironment& environment, const Definition& definition):
  Plugin {environment},
  _definition {definition} {
	// Nothing to do
}

void OptionScreen::_display() {
	_environment.canvas.fillScreen(SH110X_BLACK);

	if (_definition.icon) {
		_environment.canvas
		    .drawBitmap(48, 4, reinterpret_cast<const uint8_t*>(_definition.icon), 32, 32, SH110X_WHITE, SH110X_BLACK);
	}

	int16_t  x, y;
	uint16_t w, h;
	_environment.canvas.getTextBounds(_definition.displayName, 0, 0, &x, &y, &w, &h);
	w += 12;
	x = (_environment.canvas.width() - w) / 2;

	_environment.canvas.setTextColor(SH110X_WHITE);
	_environment.canvas.setCursor(x + 12, 40);
	_environment.canvas.print(_definition.displayName);

	if (_value) {
		_environment.canvas.fillRect(x, 40, 8, 8, SH110X_WHITE);
	} else {
		_environment.canvas.drawRect(x, 40, 8, 8, SH110X_WHITE);
	}

	_environment.canvas.display();
}

void OptionScreen::onActivate() {
	if (_definition.initialCallback) {
		_value = _definition.initialCallback();
	} else {
		_value = false;
	}
}

void OptionScreen::onResume() {
	_environment.backlight.setPixels(0, 12, Color::Black());
	_environment.backlight.setPixel(0, Color::White());
	_environment.backlight.setPixel(2, Color::Red());
	_environment.backlight.show();

	_display();
}

void OptionScreen::onKeyUp(uint8_t key) {
	if (key < 2) {
		_value = !_value;
		_definition.changeCallback(_value);
		_display();
	}

	if (key == 3) {
		navigator.close();
	}
}

const char* OptionScreen::getName() const {
	return _definition.name;
}

const char* OptionScreen::getDisplayName() const {
	return _definition.displayName;
}

const uint32_t* OptionScreen::getIcon() const {
	return _definition.icon;
}
