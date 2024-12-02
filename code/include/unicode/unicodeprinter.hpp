#pragma once

#include "wfc/iprinter.hpp"
#include "wfc/map2d.hpp"
#include <string>
class UnicodePrinter : public IPrinter<std::string> {
public:
  UnicodePrinter(Map2D<std::string> &map, int row_length)
      : map(map), row_length(row_length) {}
  std::string Print() override;

private:
  Map2D<std::string> &map;
  int row_length;
};
