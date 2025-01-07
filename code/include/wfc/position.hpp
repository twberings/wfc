#pragma once

#include "wfc/coord.hpp"
#include "wfc/imap.hpp"
#include "wfc/itile.hpp"
#include <memory>
#include <vector>
template <class T> class IMap;
template <class T> class Position {
public:
  Position(Coord coord, std::vector<std::shared_ptr<ITile<T>>> options,
           IMap<T> *map);
  int Get_entropy() const;
  Coord Get_coord() const;
  void Collapse();
  void Collapse_to(T &content);
  void Remove_options(Coord &from,
                      std::vector<std::shared_ptr<ITile<T>>> &remaining_tiles);
  std::vector<T> Output() const;
  const std::vector<std::shared_ptr<ITile<T>>> &Get_options();

private:
  void Collapse_to(std::shared_ptr<ITile<T>> tile);
  Coord coord;
  std::vector<std::shared_ptr<ITile<T>>> options;
  IMap<T> *map;
};
