#pragma once

#include "point.hpp"
#include <vector>
#include <memory>

template<class T>
class Figure {
public:
  virtual Point<double> center() = 0;

  virtual operator double() const = 0;

  virtual ~Figure() = default;

private:
  std::unique_ptr<Point<T>> point;
};