#pragma once

#include "figure.hpp"

class Rectangle : public Figure {
public:
  Rectangle() : left_down(Point(0.0, 0.0)), right_up(Point(0.0, 0.0)) {}

  Rectangle(Point left_down,
            Point right_up)
      : left_down(left_down), right_up(right_up) {}

  Rectangle(Point &left_down, double height, double width)
      : left_down(left_down) {
    right_up = Point(left_down.x + width,
                                         left_down.y + height);
  }

  Rectangle(Rectangle &other) {
    left_down = other.left_down;
    right_up = other.right_up;
  }

  Rectangle(Rectangle &&other) {
    left_down = std::move(other.left_down);
    right_up = std::move(other.right_up);
  }

  Point center() override {
    double x_center = 0.0, y_center = 0.0;
    x_center = (left_down.x + right_up.x) / 2;
    y_center = (left_down.y + right_up.y) / 2;
    return (Point(x_center, y_center));
  }

  friend std::ostream &operator<<(std::ostream &, Rectangle &s) {
    std::cout << s.left_down << ", " << s.right_up << ";";
    return std::cout;
  }

  friend std::istream &operator>>(std::istream &, Rectangle &s) {
    double x = 0.0, y = 0.0;
    std::cin >> x >> y;
    s.left_down.x = x;
    s.left_down.y = y;
    std::cin >> x >> y;
    s.right_up.x = x;
    s.right_up.y = y;
    return std::cin;
  }

  operator double() const {
    return (right_up.x - left_down.x) *
           (right_up.y - left_down.y);
  }

  Rectangle &operator=(const Rectangle &other) {
    if (*this == other) {
      return *this;
    }
    left_down = other.left_down;
    right_up = other.right_up;
    return *this;
  }

  Rectangle &operator=(Rectangle &&other) {
    if (*this == other) {
      return *this;
    }
    left_down = std::move(other.left_down);
    right_up = std::move(other.right_up);
    return *this;
  }

  bool operator==(const Rectangle &other) const {
    return (left_down == other.left_down && right_up == other.right_up);
  }

  virtual ~Rectangle() = default;

private:
  Point left_down, right_up;
};