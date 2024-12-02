#pragma once

#include "image/image.hpp"
#include "image/imagefactory.hpp"
#include "wfc/iprinter.hpp"
#include "wfc/map2d.hpp"
#include <stdexcept>
class ImagePrinter : public IPrinter<Image> {
public:
  ImagePrinter(Map2D<Image> &map, int rows, int cols)
      : map(map), rows(rows), cols(cols) {}
  Image Print() override {
    auto result = ImageFactory::assemble_image(map.Output(), rows, cols);
    if (!result) {
      throw std::runtime_error("Failed to assemble image");
    }
    return *result;
  };

private:
  Map2D<Image> &map;
  int rows;
  int cols;
};
