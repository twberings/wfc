#include "image/image.hpp"
#include <vector>
Image::Image(int width, int height, std::vector<Pixel> &pixels)
    : width(width), height(height) {
  this->pixels =
      std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      this->pixels[i][j] = pixels[i * width + j];
    }
  }
}

Image Image::Get_rotated() const {
  std::vector<Pixel> rotated_pixels(width * height);

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      rotated_pixels[col * height + (height - 1 - row)] = pixels[row][col];
    }
  }
  return Image(height, width, rotated_pixels);
}

bool Image::operator==(const Image &other) const {
  if (width != other.Get_width() || height != other.Get_height()) {
    return false;
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (pixels[i][j] != other.Get_pixel(j, i)) {
        return false;
      }
    }
  }
  return true;
}
