#include "wfc/map2d.hpp"
#include "image/image.hpp"
#include "wfc/position.hpp"
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
Map2D<T>::Map2D(int width, int height,
                std::vector<std::shared_ptr<ITile<T>>> &tileSet)
    : width(width), height(height) {
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      int coords[] = {i, j};
      positions.push_back(Position<T>(Coord(2, coords), tileSet, this));
    }
  }
}

template <class T>
std::optional<std::reference_wrapper<Position<T>>>
Map2D<T>::Get_position(Coord coord) {
  for (Position<T> &position : positions) {
    if (position.Get_coord() == coord) {
      return position;
    }
  }
  return {};
}

template <class T> const Coord Map2D<T>::Lowest_entropy() {
  int lowest_entropy_value = positions[0].Get_entropy();
  std::vector<Coord> lowest_entropy_coords;
  for (const Position<T> &position : positions) {
    if (position.Get_entropy() == 0) {
      throw std::runtime_error("Error: Entropy is 0");
    }
    if ((position.Get_entropy() < lowest_entropy_value &&
         position.Get_entropy() > 1) ||
        lowest_entropy_value == 1) {
      lowest_entropy_coords.clear();
      lowest_entropy_value = position.Get_entropy();
    }
    if (position.Get_entropy() == lowest_entropy_value) {
      lowest_entropy_coords.push_back(position.Get_coord());
    }
  }
  int random_index = rand() % lowest_entropy_coords.size();
  return lowest_entropy_coords[random_index];
}

template <class T> std::vector<std::vector<T>> Map2D<T>::Output() {
  std::vector<std::vector<T>> output;
  for (const Position<T> &position : positions) {
    output.push_back(position.Output());
  }
  return output;
}

template <class T> void Map2D<T>::Collapse_at(Coord coord) {
  auto result = Get_position(coord);
  if (result) {
    Position<T> &position = result.value().get();
    position.Collapse();
  }
}

template <class T> void Map2D<T>::Collapse_to(Coord coord, T &content) {
  auto result = Get_position(coord);
  if (result) {
    Position<T> &position = result.value().get();
    position.Collapse_to(content);
  }
}

template <class T> bool Map2D<T>::Is_solved() {
  for (const Position<T> &position : positions) {
    if (position.Get_entropy() > 1) {
      return false;
    }
  }
  return true;
}

template class Map2D<std::string>;
template class Map2D<int>;
template class Map2D<Image>;
