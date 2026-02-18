#include "PluginBacklight.hpp"

PluginBacklight::PluginBacklight(CallbackType showCallback):
  _showCallback {showCallback} {
	// Nothing to do
}

void PluginBacklight::show() {
	if (_showCallback) {
		_showCallback();
	}
}

void PluginBacklight::setPixel(uint8_t i, const Color& color) {
	if (i >= 12) {
		return;
	}

	_colors[i] = color;
}

void PluginBacklight::setPixel(uint8_t i, uint32_t color) {
	setPixel(i, Color(color));
}

void PluginBacklight::setPixel(uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
	setPixel(i, {r, g, b});
}

void PluginBacklight::setPixel(uint8_t i, uint16_t h, uint8_t s, uint8_t l) {
	setPixel(i, {h, s, l});
}

void PluginBacklight::setPixels(uint8_t i, uint8_t n, const Color& color) {
	for (uint8_t j {0}; j < n; ++j) {
		setPixel(i + j, color);
	}
}

void PluginBacklight::setPixels(uint8_t i, uint8_t n, uint32_t color) {
	setPixels(i, n, Color(color));
}

void PluginBacklight::setPixels(uint8_t i, uint8_t n, uint8_t r, uint8_t g, uint8_t b) {
	setPixels(i, n, {r, g, b});
}

void PluginBacklight::setPixels(uint8_t i, uint8_t n, uint16_t h, uint8_t s, uint8_t l) {
	setPixels(i, n, {h, s, l});
}

Color PluginBacklight::getPixel(uint8_t i) const {
	if (i >= 12) {
		return {};
	}

	return _colors[i];
}

const Color* PluginBacklight::getPixels() const {
	return _colors;
}
