#include "wfc/coord.hpp"
#include <stdexcept>
Coord::Coord(int dimension, int coords[]) : dimension(dimension) {
  this->coords = new int[dimension];
  for (int i = 0; i < dimension; i++) {
    this->coords[i] = coords[i];
  }
}

Coord::Coord(const Coord &other) : dimension(other.dimension) {
  coords = new int[dimension];
  for (int i = 0; i < dimension; i++) {
    coords[i] = other.coords[i];
  }
}

Coord &Coord::operator=(const Coord &other) {
  if (this == &other) {
    return *this;
  }
  delete[] coords;
  dimension = other.dimension;
  coords = new int[dimension];
  for (int i = 0; i < dimension; i++) {
    coords[i] = other.coords[i];
  }
  return *this;
}

bool Coord::operator<(const Coord &other) const {
  if (dimension != other.dimension) {
    return dimension < other.dimension;
  }
  for (int i = 0; i < dimension; i++) {
    if (coords[i] != other.coords[i]) {
      return coords[i] < other.coords[i];
    }
  }
  return false;
}

std::string Coord::To_string() const {
  std::string output = "(";
  for (int i = 0; i < dimension; i++) {
    output += std::to_string(coords[i]);
    if (i != dimension - 1) {
      output += ", ";
    }
  }
  output += ")";
  return output;
}

bool Coord::operator==(const Coord &other) const {
  if (dimension != other.dimension) {
    return false;
  }
  for (int i = 0; i < dimension; i++) {
    if (coords[i] != other.coords[i]) {
      return false;
    }
  }
  return true;
}

std::vector<Coord> Coord::Get_neighbors() {
  std::vector<Coord> neighbors;
  int *new_coords = new int[dimension];
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      new_coords[j] = coords[j];
    }
    new_coords[i]++;
    neighbors.push_back(Coord(dimension, new_coords));
    new_coords[i] -= 2;
    neighbors.push_back(Coord(dimension, new_coords));
  }
  delete[] new_coords;
  return neighbors;
}

int Coord::Get_direction(Coord &other) {
  if (dimension != other.dimension) {
    throw std::invalid_argument("Error: Dimensions do not match");
  }
  int axis = 0;
  bool different = false;
  for (int i = 0; i < dimension; i++) {
    if (coords[i] != other.coords[i]) {
      if (different) {
        throw std::invalid_argument("Error: Coords are not neighbors");
      }
      axis = i;
      different = true;
    }
  }
  if (!different) {
    throw std::invalid_argument("Error: Coords are not neighbors");
  }

  if (coords[axis] == other.coords[axis] + 1) {
    return axis * 2;
  }
  if (coords[axis] == other.coords[axis] - 1) {
    return (axis * 2) + 1;
  }

  throw std::invalid_argument("Error: Coords are not neighbors");
}

Coord::~Coord() { delete[] coords; }
