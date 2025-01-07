#pragma once

#include "wfc/tile2d.hpp"

class JsonTile : public Tile2d<std::string> {
public:
  JsonTile(Socket up, Socket right, Socket down, Socket left, std::string name)
      : Tile2d(up, right, down, left), name(name) {}
  std::string Output() override { return name; }

private:
  std::string name;
};
