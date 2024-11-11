#pragma once

#include <iostream>
#include <utility>

class Point {
public:
  double x, y;

public:
  Point() : x(0.0), y(0.0) {}

  Point(double x, double y) : x(x), y(y) {}

  Point(Point &other) : x(other.x), y(other.y) {}

  Point(Point &&other) : x(other.x), y(other.y) {
    other.x = 0.0;
    other.y = 0.0;
  }

  Point &operator=(const Point &other) {
    if (*this == other) return *this;
    x = other.x;
    y = other.y;
    return *this;
  }

  Point &operator=(Point &&other) {
    if (*this == other) return *this;
    x = other.x;
    y = other.y;
    other.x = 0;
    other.y = 0;
    return *this;
  }

  bool operator==(const Point &other) const {
    return (x == other.x && y == other.y);
  }

  ~Point() = default;
};

std::istream &operator>>(std::istream &, Point c) {
  std::cin >> c.x >> c.y;
  return std::cin;
}

std::ostream &operator<<(std::ostream &, Point c) {
  std::cout << "(" << c.x << ", " << c.y << ")";
  return std::cout;
}

class Figure {
public:
  virtual Point center() = 0;

  virtual operator double() const = 0;

  virtual ~Figure() = default;
};
