#include "SelectScreen.hpp"

SelectScreen::SelectScreen(PluginEnvironment& environment, const Definition& definition):
  Plugin {environment},
  _definition {definition} {
	// Nothing to do
}

void SelectScreen::_display() {
	_environment.backlight.setPixels(0, 2, Color::Purple(96));
	_environment.backlight.setPixel(2, Color::Green());
	_environment.backlight.setPixels(3, 9, Color::Black());
	_environment.backlight.show();

	_environment.canvas.fillScreen(SH110X_BLACK);

	if (_definition.icon) {
		_environment.canvas
		    .drawBitmap(48, 4, reinterpret_cast<const uint8_t*>(_definition.icon), 32, 32, SH110X_WHITE, SH110X_BLACK);
	}

	int16_t  x, y;
	uint16_t w, h;
	_environment.canvas.getTextBounds(_definition.options[_idx].displayName, 0, 0, &x, &y, &w, &h);
	int16_t halfWidth = w / 2;
	x = (_environment.canvas.width() - w) / 2;

	_environment.canvas.setTextColor(SH110X_WHITE);
	_environment.canvas.setCursor(x, 40);
	_environment.canvas.print(_definition.options[_idx].displayName);

	_environment.canvas.getTextBounds("<", 0, 0, &x, &y, &w, &h);

	if (_idx) {
		_environment.canvas.setCursor(_environment.canvas.width() / 2 - halfWidth - w - 4, 40);
		_environment.canvas.print("<");
	}
	if (_idx < sizeof(Definition::options) / sizeof(Definition::options[0])
	    && _definition.options[_idx + 1].displayName[0]) {
		_environment.canvas.setCursor(_environment.canvas.width() / 2 + halfWidth + 4, 40);
		_environment.canvas.print(">");
	}

	_environment.canvas.display();
}

void SelectScreen::_prevItem() {
	if (_idx) {
		--_idx;
	}
}

void SelectScreen::_nextItem() {
	if ((_idx < sizeof(Definition::options) / sizeof(Definition::options[0]))
	    && _definition.options[_idx + 1].displayName[0]) {
		++_idx;
	}
}

void SelectScreen::onActivate() {
	_idx = 0;
	int initialValue {0};

	if (_definition.initialCallback) {
		initialValue = _definition.initialCallback();
	}

	for (uint8_t i {0}; i < sizeof(Definition::options) / sizeof(Definition::options[0]); ++i) {
		if (initialValue == _definition.options[i].value) {
			_idx = i;
			break;
		}
	}
}

void SelectScreen::onResume() {
	_display();
}

void SelectScreen::onKeyUp(uint8_t key) {
	switch (key) {
		case 0:
			navigator.close();
			break;
		case 1:
			_prevItem();
			_display();

			if (_definition.changeCallback) {
				_definition.changeCallback(_definition.options[_idx].value);
			}
			break;
		case 2:
			_nextItem();
			_display();

			if (_definition.changeCallback) {
				_definition.changeCallback(_definition.options[_idx].value);
			}
			break;
		case 3:
			navigator.close();
	}
}

void SelectScreen::onEncoderDown(int32_t count) {
	_prevItem();
	_display();
}

void SelectScreen::onEncoderUp(int32_t count) {
	_nextItem();
	_display();
}

const char* SelectScreen::getName() const {
	return _definition.name;
}

const char* SelectScreen::getDisplayName() const {
	return _definition.displayName;
}

const uint32_t* SelectScreen::getIcon() const {
	return _definition.icon;
}
