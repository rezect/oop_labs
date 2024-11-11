#include "figure.hpp"
#include <memory>

template <class T>
class Trapeze : public Figure {
public:
  Trapeze()
      : left_down(std::make_unique<Point<T>>(T(), T())),
        left_up(std::make_unique<Point<T>>(T(), T())),
        right_up(std::make_unique<Point<T>>(T(), T())),
        right_down(std::make_unique<Point<T>>(T(), T())) {}

  Trapeze(Point<T> left_down, Point<T> left_up, Point<T> right_up, Point<T> right_down)
      : left_down(std::make_unique<Point<T>>(left_down)),
        left_up(std::make_unique<Point<T>>(left_up)),
        right_up(std::make_unique<Point<T>>(right_up)),
        right_down(std::make_unique<Point<T>>(right_down)) {}

  Point<T> center() const {
    T q = right_up->x - left_up->x;
    T p = right_down->x - left_down->x;
    T h = left_up->y - left_down->y;
    T x_center = h / 2;
    T y_center = ((2 * q + p) * h) / (3 * (p + q));

    return Point<T>(x_center, y_center);
  }

  Trapeze &operator=(const Trapeze &other) {
    if (this == &other)
      return *this;
    left_down = std::make_unique<Point<T>>(*other.left_down);
    left_up = std::make_unique<Point<T>>(*other.left_up);
    right_up = std::make_unique<Point<T>>(*other.right_up);
    right_down = std::make_unique<Point<T>>(*other.right_down);
    return *this;
  }

  Trapeze &operator=(Trapeze &&other) noexcept {
    if (this == &other)
      return *this;
    left_down = std::move(other.left_down);
    left_up = std::move(other.left_up);
    right_up = std::move(other.right_up);
    right_down = std::move(other.right_down);
    return *this;
  }

  bool operator==(const Trapeze &other) const {
    return (*left_down == *other.left_down && *left_up == *other.left_up &&
            *right_down == *other.right_down && *right_up == *other.right_up);
  }

  friend std::istream &operator>>(std::istream &in, Trapeze &c) {
    Point<T> temp_left_down, temp_left_up, temp_right_up, temp_right_down;
    in >> temp_left_down >> temp_left_up >> temp_right_up >> temp_right_down;
    c.left_down = std::make_unique<Point<T>>(temp_left_down);
    c.left_up = std::make_unique<Point<T>>(temp_left_up);
    c.right_up = std::make_unique<Point<T>>(temp_right_up);
    c.right_down = std::make_unique<Point<T>>(temp_right_down);
    return in;
  }

  friend std::ostream &operator<<(std::ostream &out, const Trapeze &c) {
    out << *c.left_down << ", " << *c.left_up << ", " << *c.right_up << ", "
        << *c.right_down << ";";
    return out;
  }

  operator double() const {
    T q = right_up->x - left_up->x;
    T p = right_down->x - left_down->x;
    T h = left_up->y - left_down->y;

    return 0.5 * (p + q) * h;
  }

private:
  std::unique_ptr<Point<T>> left_down, left_up, right_up, right_down;
};
