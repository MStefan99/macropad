#ifndef COLOR_HPP
#define COLOR_HPP

#include "Arduino.h"


class Color {
public:
  struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  };

  struct HSL {
    uint16_t h;
    uint8_t s;
    uint8_t l;
  };

  Color() = default;
  Color(const RGB& rgb);
  Color(const HSL& hsl);
  Color(uint32_t rgb);
  Color(uint8_t r, uint8_t g, uint8_t b);
  Color(uint16_t h, uint8_t s, uint8_t l);

  uint8_t getR() const;
  uint8_t getG() const;
  uint8_t getB() const;

  void setR(uint8_t r);
  void setG(uint8_t g);
  void setB(uint8_t b);

  uint16_t getH() const;
  uint8_t getS() const;
  uint8_t getL() const;

  void setH(uint16_t h);
  void setS(uint8_t s);
  void setL(uint8_t l);

  RGB getRGB() const;
  HSL getHSL() const;
  uint32_t getHex() const;

protected: 
  RGB _rgb;
};


#endif