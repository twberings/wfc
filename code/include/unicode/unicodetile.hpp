#pragma once

#include "wfc/tile2d.hpp"
#include <string>

class UnicodeTile : public Tile2d<std::string> {
public:
  UnicodeTile(int up, int right, int down, int left, std::string glyph)
      : Tile2d(up, right, down, left), glyph(glyph) {}
  std::string Output() override { return glyph; }

private:
  std::string glyph;
};
