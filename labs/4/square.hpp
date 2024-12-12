#include "rectangle.hpp"

template <class T> class Square : public Rectangle {
public:
  Square() : Rectangle() {}

  Square(Point left_down, double side) : Rectangle(left_down, side, side) {}

  operator double() const {
    return (right_up->x - left_down->x) * (right_up->y - left_down->y);
  }

  virtual ~Square() = default;
};