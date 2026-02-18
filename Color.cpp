#include "Color.hpp"

Color::HSL rgb2hsl(const Color::RGB& rgb) {
	return {};
}

Color::RGB hsl2rgb(const Color::HSL& hsl) {
	return {};
}

Color::Color(const RGB& rgb):
  _rgb {rgb} {
	// Nothing to do
}

Color::Color(const HSL& hsl):
  _rgb {hsl2rgb(hsl)} {
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

Color::Color(uint16_t h, uint8_t s, uint8_t l):
  _rgb {hsl2rgb({h, s, l})} {
	// Nothing to do
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
	return rgb2hsl(_rgb).h;
}

uint8_t Color::getS() const {
	return rgb2hsl(_rgb).s;
}

uint8_t Color::getL() const {
	return rgb2hsl(_rgb).l;
}

void Color::setH(uint16_t h) {
	auto hsl {rgb2hsl(_rgb)};

	hsl.h = h;
	_rgb = hsl2rgb(hsl);
}

void Color::setS(uint8_t s) {
	auto hsl {rgb2hsl(_rgb)};

	hsl.s = s;
	_rgb = hsl2rgb(hsl);
}

void Color::setL(uint8_t l) {
	auto hsl {rgb2hsl(_rgb)};

	hsl.l = l;
	_rgb = hsl2rgb(hsl);
}

Color::RGB Color::getRGB() const {
	return _rgb;
}

Color::HSL Color::getHSL() const {
	return rgb2hsl(_rgb);
}

uint32_t Color::getHex() const {
	return (_rgb.r << 16u) | (_rgb.g << 8u) | _rgb.b;
}
