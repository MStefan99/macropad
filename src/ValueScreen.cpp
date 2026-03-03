#include "ValueScreen.hpp"

int scale(int val, int inMin, int inMax, int outMin, int outMax) {
	if (inMin == inMax) {
		return 0;
	}

	return (val - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

ValueScreen::ValueScreen(PluginEnvironment& environment, const Definition& definition):
  Plugin {environment},
  _definition {definition} {
	// Nothing to do
}

void ValueScreen::_display() {
	_environment.backlight.setPixels(0, 12, Color::Black());
	_environment.backlight.setPixels(0, 2, Color::White());
	_environment.backlight.setPixel(2, Color::Red());
	_environment.backlight.show();

	_environment.canvas.fillScreen(SH110X_BLACK);

	if (_definition.icon) {
		_environment.canvas
		    .drawBitmap(48, 4, reinterpret_cast<const uint8_t*>(_definition.icon), 32, 32, SH110X_WHITE, SH110X_BLACK);
	}

	_environment.canvas.drawRect(16, 40, _environment.canvas.width() - 32, 8, SH110X_WHITE);
	_environment.canvas.fillRect(
	    16,
	    40,
	    scale(_value, _definition.limits.minValue, _definition.limits.maxValue, 0, _environment.canvas.width() - 32),
	    8,
	    SH110X_WHITE
	);

	_environment.canvas.display();
}

void ValueScreen::_decrement() {
	_value = min(max(_value - _definition.limits.step, _definition.limits.minValue), _definition.limits.maxValue);
}

void ValueScreen::_increment() {
	_value = min(max(_value + _definition.limits.step, _definition.limits.minValue), _definition.limits.maxValue);
}

void ValueScreen::onActivate() {
	_value = 0;

	if (_definition.initialCallback) {
		_value = _definition.initialCallback();
	}
}

void ValueScreen::onResume() {
	_display();
}

void ValueScreen::onKeyUp(uint8_t key) {
	switch (key) {
		case 0:
			navigator.close();
			break;
		case 1:
			_decrement();
			if (_definition.changeCallback) {
				_definition.changeCallback(_value);
			}
			_display();
			break;
		case 2:
			_increment();
			if (_definition.changeCallback) {
				_definition.changeCallback(_value);
			}
			_display();
			break;
		case 3:
			navigator.close();
	}
}

void ValueScreen::onEncoderDown(int32_t count) {
	_decrement();
	if (_definition.changeCallback) {
		_definition.changeCallback(_value);
	}
	_display();
}

void ValueScreen::onEncoderUp(int32_t count) {
	_increment();
	if (_definition.changeCallback) {
		_definition.changeCallback(_value);
	}
	_display();
}

const char* ValueScreen::getName() const {
	return _definition.name;
}

const char* ValueScreen::getDisplayName() const {
	return _definition.displayName;
}

const uint32_t* ValueScreen::getIcon() const {
	return _definition.icon;
}
