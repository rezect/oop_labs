#include "figure.hpp"

class Trapeze : public Figure {
public:
  Trapeze()
      : left_down(Point(0.0, 0.0)), left_up(Point(0.0, 0.0)),
        right_up(Point(0.0, 0.0)), right_down(Point(0.0, 0.0)) {}

  Trapeze(Point left_down, Point left_up, Point right_up, Point right_down)
      : left_down(left_down), left_up(left_up), right_up(right_up),
        right_down(right_down) {}

  Point center() {
    double x_center = 0.0;
    double y_center = 0.0;
    double q = right_up.x - left_up.x;
    double p = right_down.x - left_down.x;
    double h = left_up.y - left_down.y;
    x_center = h / 2;
    y_center = ((2 * q + p) * h) / (3 * (p + q));

    return Point(x_center, y_center);
  }

  Trapeze &operator=(const Trapeze &other) {
    if (*this == other) return *this;
    left_down = other.left_down;
    left_up = other.left_up;
    right_up = other.right_up;
    right_down = other.right_down;
    return *this;
  }

  Trapeze &operator=(Trapeze &&other) {
    if (*this == other) return *this;
    left_down = std::move(other.left_down);
    left_up = std::move(other.left_up);
    right_up = std::move(other.right_up);
    right_down = std::move(other.right_down);
    return *this;
  }

  bool operator==(const Trapeze &other) const {
    return (left_down == other.left_down && left_up == other.left_up && right_down == other.right_down && right_up == other.right_up);
  }

  friend std::istream &operator>>(std::istream &, Trapeze &c) {
    std::cin >> c.left_down >> c.left_up >> c.right_up >> c.right_down;
    return std::cin;
  }

  friend std::ostream &operator<<(std::ostream &, Trapeze &c) {
    std::cout << c.left_down << ", " << c.left_up << ", " << c.right_up << ", " << c.right_down << ";";
    return std::cout;
  }

  operator double() const {
    double q = right_up.x - left_up.x;
    double p = right_down.x - left_down.x;
    double h = left_up.y - left_down.y;

    return 0.5 * (p + q) * h;
  }

private:
  Point left_down, left_up, right_up, right_down;
};