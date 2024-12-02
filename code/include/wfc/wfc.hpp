#pragma once

#include "wfc/imap.hpp"
#include "wfc/iprinter.hpp"
#include <iostream>
template <class T> class WaveFunctionCollapse {
public:
  WaveFunctionCollapse(IMap<T> *map, IPrinter<T> *printer, unsigned int seed)
      : map(map), printer(printer), seed(seed) {
    srand(seed);
  }
  T Solve() {
    std::cout << "Seed: " << seed << std::endl;
    while (!map->Is_solved()) {
      Coord coord = map->Lowest_entropy();
      map->Collapse_at(coord);
    }
    return printer->Print();
  }

private:
  IMap<T> *map;
  IPrinter<T> *printer;
  unsigned int seed;
};
