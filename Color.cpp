#include "Color.hpp"

Color::HSVchannels rgb2hsv(const Color::RGBchannels& rgb) {
	Color::HSVchannels tHSV {};

	tHSV.v = max(max(rgb.r, rgb.g), rgb.b);
	uint8_t xMin = min(min(rgb.r, rgb.g), rgb.b);
	uint8_t c = tHSV.v - xMin;

	if (!c) {
		// Hue stays at 0
	} else if (tHSV.v == rgb.r) {
		tHSV.h = (((static_cast<int>(rgb.g) - static_cast<int>(rgb.b)) << 8u) / c + 1536) % 1536;
	} else if (tHSV.v == rgb.g) {
		tHSV.h = ((static_cast<int>(rgb.b) - static_cast<int>(rgb.r)) << 8u) / c + 512;
	} else if (tHSV.v == rgb.b) {
		tHSV.h = ((static_cast<int>(rgb.r) - static_cast<int>(rgb.g)) << 8u) / c + 1024;
	}

	if (tHSV.v) {
		tHSV.s = (c << 8u) / tHSV.v;
	}

	return tHSV;
}

Color::RGBchannels hsv2rgb(const Color::HSVchannels& hsv) {
	if (!hsv.s) {
		return {hsv.v, hsv.v, hsv.v};
	}

	uint16_t h = hsv.h;
	if (h >= 1536) {
		h = 1536;
	}

	Color::RGBchannels tRGB {};
	uint8_t            c = (static_cast<int>(hsv.v) * static_cast<int>(hsv.s)) >> 8u;
	uint8_t            hPiece = h >> 8u;
	uint8_t            x = static_cast<int>(c) * (256 - abs((static_cast<int>(h) % 512) - 256)) >> 8u;

	tRGB.channels[((hPiece + 1) >> 1u) % 3] = c;
	tRGB.channels[(7 - hPiece) % 3] = x;

	int16_t m = hsv.v - c;
	for (uint8_t i {0}; i < 3; ++i) {
		tRGB.channels[i] += m;
	}

	return tRGB;
}

Color::Color(const RGBchannels& rgb):
  _rgb {rgb} {
	// Nothing to do
}

Color::Color(const HSVchannels& hsv):
  _rgb {hsv2rgb(hsv)} {
	// Nothing to do
}

Color::Color(uint32_t rgb):
  _rgb {
    static_cast<uint8_t>((rgb >> 16u) & 0xff),
    static_cast<uint8_t>((rgb >> 8u) & 0xff),
    static_cast<uint8_t>(rgb & 0xff)
  } {
	// Nothing to do
}

Color::Color(uint8_t r, uint8_t g, uint8_t b):
  _rgb {r, g, b} {
	// Nothing to do
}

Color::Color(uint16_t h, uint8_t s, uint8_t v):
  _rgb {hsv2rgb({h, s, v})} {
	// Nothing to do
}

Color Color::RGB(uint8_t r, uint8_t g, uint8_t b) {
	return Color(r, g, b);
}

Color Color::HSV(uint16_t h, uint8_t s, uint8_t v) {
	return Color(h, s, v);
}

uint8_t Color::getR() const {
	return _rgb.r;
}

uint8_t Color::getG() const {
	return _rgb.g;
}

uint8_t Color::getB() const {
	return _rgb.b;
}

void Color::setR(uint8_t r) {
	_rgb.r = r;
}

void Color::setG(uint8_t g) {
	_rgb.g = g;
}

void Color::setB(uint8_t b) {
	_rgb.b = b;
}

uint16_t Color::getH() const {
	return rgb2hsv(_rgb).h;
}

uint8_t Color::getS() const {
	return rgb2hsv(_rgb).s;
}

uint8_t Color::getV() const {
	return rgb2hsv(_rgb).v;
}

void Color::setH(uint16_t h) {
	auto hsv {rgb2hsv(_rgb)};

	hsv.h = h;
	_rgb = hsv2rgb(hsv);
}

void Color::setS(uint8_t s) {
	auto hsv {rgb2hsv(_rgb)};

	hsv.s = s;
	_rgb = hsv2rgb(hsv);
}

void Color::setV(uint8_t v) {
	auto hsv {rgb2hsv(_rgb)};

	hsv.v = v;
	_rgb = hsv2rgb(hsv);
}

Color::RGBchannels Color::getRGB() const {
	return _rgb;
}

Color::HSVchannels Color::getHSV() const {
	return rgb2hsv(_rgb);
}

uint32_t Color::getHex() const {
	return (_rgb.r << 16u) | (_rgb.g << 8u) | _rgb.b;
}
