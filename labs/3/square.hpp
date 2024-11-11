#include "rectangle.hpp"

class Square : public Rectangle {
public:
  Square() : Rectangle() {}

  Square(Point left_down, double side) : Rectangle(left_down, side, side) {}

  virtual ~Square() = default;
};