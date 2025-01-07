#pragma once

#include "wfc/itile.hpp"
#include <array>
#include <memory>
#include <vector>

class Socket {
public:
  Socket(int id, std::vector<int> allowed) : id(id), allowed(allowed) {}
  bool operator==(const Socket &other) const {
    for (const int &i : allowed) {
      if (i == other.id) {
        return true;
      }
    }
    return false;
  }

private:
  int id;
  std::vector<int> allowed;
};

template <class T> class Tile2d : public ITile<T> {
public:
  Tile2d(int up, int right, int down, int left)
      : sockets({Socket(left, std::vector<int>{left}),
                 Socket(right, std::vector<int>{right}),
                 Socket(up, std::vector<int>{up}),
                 Socket(down, std::vector<int>{down})}) {}

  Tile2d(Socket up, Socket right, Socket down, Socket left)
      : sockets({left, right, up, down}) {}

  virtual bool Check_constraints(std::shared_ptr<ITile<T>> &other_tile,
                                 int direction) override {
    std::shared_ptr<Tile2d<T>> other_tile2d =
        std::dynamic_pointer_cast<Tile2d<T>>(other_tile);
    if (!other_tile2d) {
      return false;
    }
    std::vector<Socket> other_sockets = other_tile2d->Get_sockets();
    if (direction % 2 == 0) {
      return sockets[direction] == other_sockets[direction + 1];
    } else {
      return sockets[direction] == other_sockets[direction - 1];
    }
  }

  std::vector<Socket> Get_sockets() {
    std::vector<Socket> output;
    for (int i = 0; i < 4; i++) {
      output.push_back(sockets[i]);
    }
    return output;
  }

  virtual ~Tile2d() {}

protected:
  std::array<Socket, 4> sockets;
};
