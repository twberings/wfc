#include "image/imagefactory.hpp"
#include "image/imageprinter.hpp"
#include "tilesets/circuit.hpp"
#include "wfc/iprinter.hpp"
#include "wfc/map2d.hpp"

#include <emscripten/bind.h>
Map2D<Image> *map;
IPrinter<Image> *printer;

void createImage(int width, int height, int seed) {
  srand(seed);
  populate_circuits("/web/tilesets/circuit");
  map = new Map2D<Image>(width, height, circuit);
  printer = new ImagePrinter(*map, height, width);
  Image image = dynamic_cast<ImagePrinter *>(printer)->Print();
  ImageFactory::save_bitmap("/output.bmp", image);
}

void nextStep() {
  if (!map->Is_solved()) {
    map->Collapse_at(map->Lowest_entropy());
    Image image = printer->Print();
    ImageFactory::save_bitmap("/output.bmp", image);
  }
}

EMSCRIPTEN_BINDINGS(module) {
  emscripten::function("createImage", &createImage);
  emscripten::function("nextStep", &nextStep);
}
