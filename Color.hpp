#ifndef COLOR_HPP
#define COLOR_HPP

#include "Arduino.h"

class Color {
public:
	struct RGBchannels {
		union {
			struct {
				uint8_t r;
				uint8_t g;
				uint8_t b;
			};

			uint8_t channels[3];
		};
	};

	struct HSVchannels {
		uint16_t h;
		uint8_t  s;
		uint8_t  v;
	};

	Color() = default;
	Color(const RGBchannels& rgb);
	Color(const HSVchannels& hsv);
	Color(uint32_t rgb);
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(uint16_t h, uint8_t s = 255, uint8_t v = 255);

	static Color RGB(uint8_t r, uint8_t g, uint8_t b);
	static Color HSV(uint16_t h, uint8_t s = 255, uint8_t v = 255);

	uint8_t getR() const;
	uint8_t getG() const;
	uint8_t getB() const;

	void setR(uint8_t r);
	void setG(uint8_t g);
	void setB(uint8_t b);

	uint16_t getH() const;
	uint8_t  getS() const;
	uint8_t  getV() const;

	void setH(uint16_t h);
	void setS(uint8_t s);
	void setV(uint8_t l);

	RGBchannels getRGB() const;
	HSVchannels getHSV() const;
	uint32_t    getHex() const;

	static Color Red(uint8_t s = 255, uint8_t v = 255) {
		return HSV(0, s, v);
	}

	static Color Orange(uint8_t s = 255, uint8_t v = 255) {
		return HSV(128, s, v);
	}

	static Color Yellow(uint8_t s = 255, uint8_t v = 255) {
		return HSV(256, s, v);
	}

	static Color Green(uint8_t s = 255, uint8_t v = 255) {
		return HSV(512, s, v);
	}

protected:
	RGBchannels _rgb;
};


#endif
