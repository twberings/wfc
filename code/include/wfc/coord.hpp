#pragma once

#include <string>
#include <vector>
class Coord {
public:
  Coord(int dimension, int coords[]);
  Coord(const Coord &other);
  ~Coord();
  std::string To_string() const;
  std::vector<Coord> Get_neighbors();
  int Get_direction(Coord &other);
  Coord &operator=(const Coord &other);
  bool operator<(const Coord &other) const;
  bool operator==(const Coord &other) const;

private:
  int dimension;
  int *coords;
};
