#pragma once

#include "wfc/itile.hpp"

#include <gmock/gmock.h>

class MTile : public ITile<int> {
public:
  MOCK_METHOD(bool, Check_constraints,
              (std::shared_ptr<ITile<int>> & other_tile, int direction));
  MOCK_METHOD(std::vector<int>, Get_sockets, ());
  MOCK_METHOD(int, Output, ());
};
