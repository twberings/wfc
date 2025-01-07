#pragma once

#include <cstdint>
class Pixel {
public:
  Pixel() : red(0), green(0), blue(0) {}
  Pixel(uint8_t red, uint8_t green, uint8_t blue)
      : red(red), green(green), blue(blue) {}
  bool operator==(const Pixel &other) const {
    return red == other.red && green == other.green && blue == other.blue;
  }
  bool operator!=(const Pixel &other) const { return !(*this == other); }
  uint8_t get_red() const { return red; }
  uint8_t get_green() const { return green; }
  uint8_t get_blue() const { return blue; }

private:
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
