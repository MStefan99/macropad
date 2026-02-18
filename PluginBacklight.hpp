#ifndef PLUGIN_BACKLIGHT_HPP
#define PLUGIN_BACKLIGHT_HPP


#include "Arduino.h"

#include "Color.hpp"


class PluginBacklight {
public:
	using CallbackType = void (*)();

	PluginBacklight(CallbackType showCallback = nullptr);

	void setPixel(uint8_t i, const Color& color);
	void setPixel(uint8_t i, uint32_t color);
	void setPixel(uint8_t i, uint8_t r, uint8_t g, uint8_t b);
	void setPixel(uint8_t i, uint16_t h, uint8_t s, uint8_t l);

	void setPixels(uint8_t i, uint8_t n, const Color& color);
	void setPixels(uint8_t i, uint8_t n, uint32_t color);
	void setPixels(uint8_t i, uint8_t n, uint8_t r, uint8_t g, uint8_t b);
	void setPixels(uint8_t i, uint8_t n, uint16_t h, uint8_t s, uint8_t y);

	void show();

	Color getPixel(uint8_t i) const;
	const Color* getPixels() const;

protected:
	Color     _colors[12];
	CallbackType _showCallback {};
};

#endif
