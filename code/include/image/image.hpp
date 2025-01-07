#pragma once

#include "image/pixel.hpp"
#include <vector>

class Image {
private:
  int width;
  int height;
  std::vector<std::vector<Pixel>> pixels;

public:
  Image() : width(0), height(0) {}
  Image(int width, int height, std::vector<Pixel> &pixels);
  Image(int columns, int rows, std::vector<Image> &images);
  int Get_width() const { return width; }
  int Get_height() const { return height; }
  Pixel Get_pixel(int x, int y) const { return pixels[y][x]; }
  Image Get_rotated() const;
  bool operator==(const Image &other) const;

  friend class ImageTile;
  friend class ImageFactory;
};
