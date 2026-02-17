#ifndef PLUGIN_BACKLIGHT_HPP
#define PLUGIN_BACKLIGHT_HPP

#include "Arduino.h"

class PluginBacklight {
public:
	using CallbackType = void (*)();

	PluginBacklight(CallbackType updateCallback = nullptr);

	void setPixel(uint8_t i, uint32_t color);
	void setPixelRGB(uint8_t i, uint8_t r, uint8_t g, uint8_t b);
	void setPixelHSY(uint8_t i, uint16_t h, uint8_t s, uint8_t y);

	void setPixels(uint8_t i, uint8_t n, uint32_t color);
	void setPixelsRGB(uint8_t i, uint8_t n, uint8_t r, uint8_t g, uint8_t b);
	void setPixelsHSY(uint8_t i, uint8_t n, uint16_t h, uint8_t s, uint8_t y);

	void update();

	uint32_t* getBuffer();

protected:
	uint32_t     buffer[12] {};
	CallbackType _updateCallback {};
};

#endif
