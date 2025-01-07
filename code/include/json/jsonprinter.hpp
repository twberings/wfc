#pragma once
#include "wfc/iprinter.hpp"
#include "wfc/map2d.hpp"
#include <string>

class JsonTilePrinter : public IPrinter<std::string> {
public:
  JsonTilePrinter(Map2D<std::string> &map, int rows, int cols)
      : map(map), rows(rows), cols(cols) {}
  std::string Print() override;

private:
  std::string VectorToString(std::vector<std::string> &vec,
                             bool with_quotes = false);
  Map2D<std::string> &map;
  int rows;
  int cols;
};
