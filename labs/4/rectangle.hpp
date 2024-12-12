#pragma once

#include "figure.hpp"
#include <memory>

template <class T>
class Rectangle : public Figure {
public:
  Rectangle()
      : left_down(std::make_unique<Point<T>>(T(), T())),
        right_up(std::make_unique<Point<T>>(T(), T())) {}

  Rectangle(Point<T> left_down, Point<T> right_up)
      : left_down(std::make_unique<Point<T>>(left_down)),
        right_up(std::make_unique<Point<T>>(right_up)) {}

  Rectangle(Point<T> &left_down, double height, double width)
      : left_down(std::make_unique<Point<T>>(left_down)) {
    right_up = std::make_unique<Point<T>>(left_down.x + width, left_down.y + height);
  }

  Rectangle(const Rectangle &other) {
    left_down = std::make_unique<Point<T>>(*other.left_down);
    right_up = std::make_unique<Point<T>>(*other.right_up);
  }

  Rectangle(Rectangle &&other) noexcept
      : left_down(std::move(other.left_down)),
        right_up(std::move(other.right_up)) {}

  Point<T> center() const override {
    T x_center = (left_down->x + right_up->x) / 2;
    T y_center = (left_down->y + right_up->y) / 2;
    return Point<T>(x_center, y_center);
  }

  friend std::ostream &operator<<(std::ostream &out, const Rectangle &s) {
    out << *s.left_down << ", " << *s.right_up << ";";
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Rectangle &s) {
    T x = T(), y = T();
    in >> x >> y;
    s.left_down = std::make_unique<Point<T>>(x, y);
    in >> x >> y;
    s.right_up = std::make_unique<Point<T>>(x, y);
    return in;
  }

  operator double() const {
    return (right_up->x - left_down->x) * (right_up->y - left_down->y);
  }

  Rectangle &operator=(const Rectangle &other) {
    if (this == &other) {
      return *this;
    }
    left_down = std::make_unique<Point<T>>(*other.left_down);
    right_up = std::make_unique<Point<T>>(*other.right_up);
    return *this;
  }

  Rectangle &operator=(Rectangle &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    left_down = std::move(other.left_down);
    right_up = std::move(other.right_up);
    return *this;
  }

  bool operator==(const Rectangle &other) const {
    return (*left_down == *other.left_down && *right_up == *other.right_up);
  }

  virtual ~Rectangle() = default;

private:
  std::unique_ptr<Point<T>> left_down, right_up;
};
