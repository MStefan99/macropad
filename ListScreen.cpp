#include "ListScreen.hpp"

ListScreen::ListScreen(PluginEnvironment& environment, const Definition& definition):
  Plugin {environment},
  _definition {definition} {
	// Nothing to do
}

void ListScreen::_displayItems() {
	_environment.canvas.fillScreen(SH110X_BLACK);
	_environment.canvas.setTextColor(SH110X_WHITE);

	if (_leftItem) {
		_environment.canvas.drawRoundRect(-6, 4, 12, 46, 4, SH110X_WHITE);
	}

	if (_leftItem != (sizeof(Definition::items) / sizeof(Definition::items[0]) - 2)) {
		if (_definition.items[_leftItem + 2].displayName[0]) {
			_environment.canvas.drawRoundRect(_environment.canvas.width() - 6, 4, 12, 46, 4, SH110X_WHITE);
		}
	}

	for (uint8_t i {0}; i < 2; ++i) {
		uint8_t idx = _leftItem + i;

		auto     bgColor {idx == _activeItem ? SH110X_WHITE : SH110X_BLACK};
		auto     fgColor {idx == _activeItem ? SH110X_BLACK : SH110X_WHITE};
		int16_t  x = 14 + 54 * i, y;
		uint16_t w, h;

		_environment.canvas.fillRoundRect(x, 4, 46, 46, 4, bgColor);
		if (idx != _activeItem) {
			_environment.canvas.drawRoundRect(x, 4, 46, 46, 4, fgColor);
		}

		auto item {_definition.items[idx]};

		if (item.icon) {
			_environment.canvas.drawBitmap(21 + 54 * i, 7, item.icon, 32, 32, bgColor, fgColor);
		}

		_environment.canvas.getTextBounds(item.displayName, 0, 0, &x, &y, &w, &h);
		_environment.canvas.setTextColor(fgColor);
		_environment.canvas.setCursor(37 + 54 * i - w / 2, 41);
		_environment.canvas.print(item.displayName);
	}

	_environment.canvas.display();
}

void ListScreen::_prevItem() {
	if (_activeItem) {
		--_activeItem;
	}
	if (_activeItem < _leftItem) {
		_leftItem = _activeItem;
	}
}

void ListScreen::_nextItem() {
	if (_activeItem != (sizeof(Definition::items) / sizeof(Definition::items[0]) - 1)) {
		if (_definition.items[_activeItem + 1].displayName[0]) {
			++_activeItem;
		}
	}
	if (_activeItem - _leftItem > 1) {
		_leftItem = _activeItem - 1;
	}
}

void ListScreen::onActivate() {
	_activeItem = _leftItem = 0;

	_environment.backlight.setPixels(0, 2, Color::White());
	_environment.backlight.setPixel(2, Color::Red());
	_environment.backlight.setPixels(3, 2, Color::Cyan());
	_environment.backlight.setPixel(5, Color::Green());
	_environment.backlight.setPixels(6, 6, Color::Black());
	_environment.backlight.show();

	_displayItems();
}

void ListScreen::onKeyDown(uint8_t key) {
	switch (key) {
		case 1: {
			_activeItem = _leftItem;
			_displayItems();
			break;
		}
		case 2: {
			_activeItem = _leftItem + 1;
			_displayItems();
			break;
		}
		case 4: {
			_prevItem();
			_displayItems();
			break;
		}
		case 5: {
			_nextItem();
			_displayItems();
			break;
		}
	}
}

void ListScreen::onKeyUp(uint8_t key) {
	switch (key) {
		case 0:
		case 6: {
			_definition.items[_activeItem].callback();
			break;
		}
		case 1: {
			_definition.items[_leftItem].callback();
			break;
		}
		case 2: {
			_definition.items[_leftItem + 1].callback();
			break;
		}
		case 3: {
			navigator.close();
			break;
		}
	}
}

void ListScreen::onEncoderDown(int32_t count) {
	_prevItem();
	_displayItems();
}

void ListScreen::onEncoderUp(int32_t count) {
	_nextItem();
	_displayItems();
}

const char* ListScreen::getName() const {
	return _definition.name;
}

const char* ListScreen::getDisplayName() const {
	return _definition.displayName;
}

const uint8_t* ListScreen::getIcon() const {
	return _definition.icon;
}
