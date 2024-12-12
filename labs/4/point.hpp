#pragma once

#include <iostream>
#include <utility>

template <class T> class Point {
public:
  T x, y;

public:
  Point() : x(T()), y(T()) {}

  Point(T x = T(), T y = T()) : x(x), y(y) {}

  Point(Point &other) : x(other.x), y(other.y) {}

  Point(Point &&other) : x(other.x), y(other.y) {}

  Point &operator=(const Point &other) {
    if (*this == other)
      return *this;
    x = other.x;
    y = other.y;
    return *this;
  }

  Point &operator=(Point &&other) {
    if (*this == other)
      return *this;
    x = other.x;
    y = other.y;
    return *this;
  }

  bool operator==(const Point &other) const {
    return (x == other.x && y == other.y);
  }

  ~Point() = default;
};

std::istream &operator>>(std::istream &, Point<double> c) {
  std::cin >> c.x >> c.y;
  return std::cin;
}

std::ostream &operator<<(std::ostream &, Point<double> c) {
  std::cout << "(" << c.x << ", " << c.y << ")";
  return std::cout;
}
