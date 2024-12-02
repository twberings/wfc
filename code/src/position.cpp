#include "wfc/position.hpp"
#include "image/image.hpp"
#include "wfc/itile.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <string>

template <class T>
Position<T>::Position(Coord coord,
                      std::vector<std::shared_ptr<ITile<T>>> options,
                      IMap<T> *map)
    : coord(coord), options(options), map(map) {}

template <class T> int Position<T>::Get_entropy() const {
  return options.size();
}

template <class T> std::vector<T> Position<T>::Output() const {
  std::vector<T> output;
  for (auto option : options) {
    output.push_back(option->Output());
  }
  return output;
}

template <class T> Coord Position<T>::Get_coord() const { return coord; }

template <class T> void Position<T>::Collapse() {
  if (options.size() < 1) {
    return;
  }
  int random_index = rand() % options.size();
  std::shared_ptr<ITile<T>> chosen_tile = options[random_index];
  std::vector<std::shared_ptr<ITile<T>>> removed_tiles = options;
  options.clear();
  options.push_back(chosen_tile);
  for (const auto &neighbor_coord : coord.Get_neighbors()) {
    auto result = map->Get_position(neighbor_coord);
    if (result.has_value()) {
      Position<T> &neighbor = result.value().get();
      neighbor.Remove_options(coord, options);
    }
  }
}

template <class T>
void Position<T>::Remove_options(
    Coord &from, std::vector<std::shared_ptr<ITile<T>>> &remaining_tiles) {
  size_t nr_options = options.size();
  std::vector<std::shared_ptr<ITile<T> >> tiles_to_remove;
  for (auto option : options) {
    bool possible = false;
    for (auto &tile : remaining_tiles) {
      if (option->Check_constraints(tile, coord.Get_direction(from))) {
        possible = true;
      }
    }
    if (!possible) {
      tiles_to_remove.push_back(option);
    }
  }
  for (auto tile : tiles_to_remove) {
    options.erase(std::remove(options.begin(), options.end(), tile),
                  options.end());
  }
  if (options.size() == 0) {
    throw std::runtime_error("Error: No options left");
  }
  if (options.size() != nr_options) {
    for (const auto &neighbor_coord : coord.Get_neighbors()) {
      auto result = map->Get_position(neighbor_coord);
      if (result.has_value()) {
        Position<T> &neighbor = result.value().get();
        neighbor.Remove_options(coord, options);
      }
    }
  }
}

template <class T>
const std::vector<std::shared_ptr<ITile<T>>> &Position<T>::Get_options() {
  return options;
}

template class Position<std::string>;
template class Position<int>;
template class Position<Image>;
