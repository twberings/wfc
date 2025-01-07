#pragma once

#include "wfc/coord.hpp"
#include "wfc/position.hpp"
#include <optional>

template <class T> class Position;
template <class T> class IMap {
public:
  virtual std::optional<std::reference_wrapper<Position<T>>>
  Get_position(Coord coord) = 0;
  virtual const Coord Lowest_entropy() = 0;
  virtual void Collapse_at(Coord coord) = 0;
  virtual void Collapse_to(Coord coord, T &content) = 0;
  virtual bool Is_solved() = 0;
  virtual ~IMap() {}
};
