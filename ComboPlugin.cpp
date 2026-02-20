#include "ComboPlugin.hpp"

constexpr static uint16_t topMargin {16};
constexpr static char     modeLabels[][8] {"Key", "Layer", "Knob"};

ComboPlugin::ComboPlugin(PluginEnvironment& environment, const Definition& definition):
  Plugin {environment},
  _definition {definition} {
	// Nothing to do
}

void ComboPlugin::_printLabel(uint8_t idx, const char* label) {
	int16_t  x, y;
	uint16_t w, h;
	_environment.canvas.getTextBounds(label, 0, 0, &x, &y, &w, &h);

	uint8_t j = idx / 3;
	uint8_t i = idx % 3;
	y = h * j + topMargin;

	_environment.canvas.setTextColor(SH110X_WHITE);

	switch (i) {
		case 0:
			_environment.canvas.setCursor(0, y);
			_environment.canvas.print(label);
			break;
		case 1:
			_environment.canvas.setCursor((_environment.canvas.width() - w) / 2, y);
			_environment.canvas.print(label);
			break;
		case 2:
			_environment.canvas.setCursor(_environment.canvas.width() - w, y);
			_environment.canvas.print(label);
			break;
	}
}

void ComboPlugin::_displayLayer() {
	int16_t  x, y;
	uint16_t w, h;

	{
		auto* displayName {_definition.layerDefinitions[_layerKey - 1].displayName};

		if (displayName[0]) {
			_environment.canvas.getTextBounds(displayName, 0, 0, &x, &y, &w, &h);
			w += 2;
			h += 2;

			_environment.canvas.fillRect(0, 0, w, h, SH110X_WHITE);
			_environment.canvas.setTextColor(SH110X_BLACK);
			_environment.canvas.setCursor(1, 1);
			_environment.canvas.print(displayName);
		}
	}

	{
		auto* encoderDisplayName {_definition.encoderDefinitions[_layerKey - 1].displayName};

		if (encoderDisplayName[0]) {
			_environment.canvas.getTextBounds(encoderDisplayName, 0, 0, &x, &y, &w, &h);
			w += 2;
			h += 2;

			x = _environment.canvas.width() - w;
			_environment.canvas.fillRect(x, 0, w, h, SH110X_WHITE);
			_environment.canvas.setTextColor(SH110X_BLACK);
			_environment.canvas.setCursor(x + 1, 1);
			_environment.canvas.print(encoderDisplayName);
		}
	}

	for (uint8_t i {0}; i < 12; ++i) {
		_environment.backlight.setPixel(i, _definition.layerDefinitions[_layerKey - 1].keyDefinitions[i].color);
		_printLabel(i, _definition.layerDefinitions[_layerKey - 1].keyDefinitions[i].displayName);
	}
}

void ComboPlugin::_display(bool peek) {
	_environment.canvas.fillScreen(SH110X_BLACK);

	if (peek) {
		_displayLayer();
	} else {
		int16_t  x, y;
		uint16_t w, h;
		_environment.canvas.getTextBounds(modeLabels[static_cast<uint8_t>(_displayMode)], 0, 0, &x, &y, &w, &h);
		w += 2;
		h += 2;
		_environment.canvas.fillRect(0, 0, w, h, SH110X_WHITE);
		_environment.canvas.setTextColor(SH110X_BLACK);
		_environment.canvas.setCursor(1, 1);
		_environment.canvas.print(modeLabels[static_cast<uint8_t>(_displayMode)]);

		_environment.canvas.getTextBounds(_definition.encoderDefinitions[_encoderMode].displayName, 0, 0, &x, &y, &w, &h);
		w += 2;
		h += 2;
		x = _environment.canvas.width() - w;
		_environment.canvas.fillRect(x, 0, w, h, SH110X_WHITE);
		_environment.canvas.setTextColor(SH110X_BLACK);
		_environment.canvas.setCursor(x + 1, 1);
		_environment.canvas.print(_definition.encoderDefinitions[_encoderMode].displayName);

		switch (_displayMode) {
			case DisplayMode::KEY:
				for (uint8_t i {0}; i < 12; ++i) {
					_environment.backlight.setPixel(i, _definition.keyDefinitions[i].color);
					_printLabel(i, _definition.keyDefinitions[i].displayName);
				}
				break;
			case DisplayMode::LAYER:
				for (uint8_t i {0}; i < 12; ++i) {
					_environment.backlight.setPixel(i, _definition.layerDefinitions[i].color);
					_printLabel(i, _definition.layerDefinitions[i].displayName);
				}
				break;
			case DisplayMode::ENCODER:
				for (uint8_t i {0}; i < 12; ++i) {
					_environment.backlight.setPixel(i, _definition.encoderDefinitions[i].color);
					_printLabel(i, _definition.encoderDefinitions[i].displayName);
				}
				break;
		}
	}

	_environment.backlight.show();
	_environment.canvas.display();
}

void ComboPlugin::onActivate() {
	_layerKey = 0;
	_comboActivated = false;
	_encoderMode = 0;
	_displayMode = DisplayMode::KEY;
}

void ComboPlugin::onResume() {
	_display();
}

void ComboPlugin::onKeyDown(uint8_t key) {
	if (!key) {               // Encoder
		                        // Do nothing
	} else if (!_layerKey) {  // Activate layer
		_layerKey = key;
		_display(true);
	} else {  // Layer already active
		auto kd {_definition.layerDefinitions[_layerKey - 1].keyDefinitions[key - 1]};
		_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
		_comboActivated = true;
	}
}

void ComboPlugin::onKeyUp(uint8_t key) {
	if (!key) {                                                                                 // Encoder
		if (!_layerKey) {                                                                         // No layer
			_displayMode = static_cast<DisplayMode>((static_cast<uint8_t>(_displayMode) + 1) % 3);  // Switch display mode
		} else {                                                                                  // Layer selected
			_encoderMode = _layerKey - 1;                                                           // Switch encoder mode
			_layerKey = 0;                                                                          // Deactivate layer
		}
		_display();
	} else if (key == _layerKey) {  // Layer released
		_layerKey = 0;                // Deactivate layer

		if (!_comboActivated) {  // No other key was pressed
			auto kd {_definition.keyDefinitions[key - 1]};
			_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
		}
		_comboActivated = false;

		_display();
	}
}

void ComboPlugin::onEncoderDown(int32_t count) {
	auto kd {_definition.encoderDefinitions[_encoderMode].encoderKeys[0]};
	_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
}

void ComboPlugin::onEncoderUp(int32_t count) {
	auto kd {_definition.encoderDefinitions[_encoderMode].encoderKeys[1]};
	_environment.keyDispatcher.dispatch(kd.keys, kd.consumerKey);
}

const char* ComboPlugin::getName() const {
	return _definition.name;
}

const char* ComboPlugin::getDisplayName() const {
	return _definition.displayName;
}

const uint8_t* ComboPlugin::getIcon() const {
	return _definition.icon;
}
