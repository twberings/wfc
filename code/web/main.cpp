#include "wfc/iprinter.hpp"
#include "wfc/map2d.hpp"

#include "json/jsonprinter.hpp"
#include "json/jsontile.hpp"
#include <emscripten/bind.h>
Map2D<std::string> *map;
IPrinter<std::string> *printer;
std::vector<std::shared_ptr<ITile<std::string>>> tileset;

void populate_tileset() {
  Socket s1(1, {1,2});
  Socket s2(2, {1,3});
  Socket s3(3, {3,2});
  JsonTile test1(s1, s1, s1, s1, "test1");
  JsonTile test2(s2, s2, s2, s2, "test2");
  JsonTile test3(s3, s3, s3, s3, "test3");
  tileset.push_back(std::make_shared<JsonTile>(test1));
  tileset.push_back(std::make_shared<JsonTile>(test2));
  tileset.push_back(std::make_shared<JsonTile>(test3));
}

std::string createImage(int width, int height, int seed) {
  srand(seed);
  populate_tileset();
  map = new Map2D<std::string>(width, height, tileset);
  printer = new JsonTilePrinter(*map, height, width);
  return printer->Print();
}

std::string nextStep() {
  if (!map->Is_solved()) {
    map->Collapse_at(map->Lowest_entropy());
  }
  return printer->Print();
}

std::string collapseTo(int x, int y, std::string tile) {
  int coords[] = {x, y};
  map->Collapse_to(Coord(2, coords), tile);
  return printer->Print();
}

EMSCRIPTEN_BINDINGS(module) {
  emscripten::function("createImage", &createImage);
  emscripten::function("nextStep", &nextStep);
  emscripten::function("collapseTo", &collapseTo);
}
