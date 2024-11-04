#pragma once

#include <iostream>
#include <utility>

class Coords {
public:
  double x, y;

public:
  Coords() : x(0.0), y(0.0) {}

  Coords(double x, double y) : x(x), y(y) {}

  Coords(Coords &other) : x(other.x), y(other.y) {}

  Coords(Coords &&other) : x(other.x), y(other.y) {
    other.x = 0.0;
    other.y = 0.0;
  }

  Coords &operator=(const Coords &other) {
    if (*this == other) return *this;
    x = other.x;
    y = other.y;
    return *this;
  }

  Coords &operator=(Coords &&other) {
    if (*this == other) return *this;
    x = other.x;
    y = other.y;
    other.x = 0;
    other.y = 0;
    return *this;
  }

  bool operator==(const Coords &other) const {
    return (x == other.x && y == other.y);
  }

  ~Coords() = default;
};

std::istream &operator>>(std::istream &, Coords c) {
  std::cin >> c.x >> c.y;
  return std::cin;
}

std::ostream &operator<<(std::ostream &, Coords c) {
  std::cout << "(" << c.x << ", " << c.y << ")";
  return std::cout;
}

class Figure {
public:
  virtual Coords center() = 0;

  virtual operator double() const = 0;

  virtual ~Figure() = default;
};
