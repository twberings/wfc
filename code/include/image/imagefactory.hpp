#pragma once

#include "image/image.hpp"
#include <optional>
#include <string>
#include <vector>

class ImageFactory {
public:
  ImageFactory() = delete;
  ImageFactory(ImageFactory &other) = delete;
  void operator=(const ImageFactory &) = delete;

  static std::optional<Image> load_bitmap(std::string path);
  static void save_bitmap(std::string path, const Image &image);
  static std::optional<Image>
  assemble_image(std::vector<std::vector<Image>> images, int rows, int cols);

private:
  static Pixel get_average_pixel(std::vector<Pixel> pixels);
};
