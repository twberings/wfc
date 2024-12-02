#pragma once

#include <memory>
template <class T> class ITile {
public:
  virtual bool Check_constraints(std::shared_ptr<ITile<T>> &other_tile,
                                 int direction) = 0;
  virtual T Output() = 0;
  virtual ~ITile() {}
};
