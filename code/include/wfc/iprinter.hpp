#pragma once

template <class T> class IPrinter {
  public:
    virtual T Print() = 0;
};
