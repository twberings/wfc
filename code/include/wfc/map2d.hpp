#pragma once

#include "wfc/imap.hpp"
#include "wfc/itile.hpp"
#include "wfc/position.hpp"
#include <memory>
#include <vector>
template <class T> class Map2D : public IMap<T> {
public:
  Map2D(int width, int height, std::vector<std::shared_ptr<ITile<T>>> &tileSet);
  std::optional<std::reference_wrapper<Position<T>>>
  Get_position(Coord coord) override;
  const Coord Lowest_entropy() override;
  void Collapse_at(Coord coord) override;
  void Collapse_to(Coord coord, T &content) override;
  bool Is_solved() override;
  std::vector<std::vector<T>> Output();

private:
  int width;
  int height;

  std::vector<Position<T>> positions;
};
