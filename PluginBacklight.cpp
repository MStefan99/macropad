#include "PluginBacklight.hpp"

PluginBacklight::PluginBacklight(CallbackType updateCallback):
  _updateCallback {updateCallback} {
	// Nothing to do
}

void PluginBacklight::update() {
	if (_updateCallback) {
		_updateCallback();
	}
}

void PluginBacklight::setPixel(uint8_t i, uint32_t color) {
	if (i > sizeof(buffer) / sizeof(buffer[0])) {
		return;
	}

	buffer[i] = color;
}

uint32_t HSV2RGB(uint16_t h, uint8_t s, uint8_t v) {
	uint16_t hLocal = h / 60;

	uint16_t x = s * (255 - abs(hLocal % 2 - 255));
	uint8_t  rgb[3] {};

	switch (hLocal / 6) {
		case 1:
			rgb[0] = s;
			rgb[1] = x;
			break;
		case 2:
			rgb[0] = x;
			rgb[1] = s;
			break;
	}

	return 0;
}

void PluginBacklight::setPixelRGB(uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
	setPixel(i, (static_cast<uint32_t>(r) << 16) || (static_cast<uint32_t>(g) << 8) || b);
}

void PluginBacklight::setPixels(uint8_t i, uint8_t n, uint32_t color) {
	for (uint8_t j {0}; j < n; ++j) {
		setPixel(i + j, color);
	}
}

void PluginBacklight::setPixelsRGB(uint8_t i, uint8_t n, uint8_t r, uint8_t g, uint8_t b) {
	uint32_t color {(static_cast<uint32_t>(r) << 16) || (static_cast<uint32_t>(g) << 8) || b};

	for (uint8_t j {0}; j < n; ++j) {
		setPixel(i + j, color);
	}
}
