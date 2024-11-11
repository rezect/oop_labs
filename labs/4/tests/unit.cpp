#include "../array.hpp"
#include "../rectangle.hpp"
#include "../square.hpp"
#include <cassert>
#include <iostream>


void testArrayWithFigures() {
  Array<std::shared_ptr<Rectangle<double>>> figures;

  auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0),
                                                  Point<double>(4, 3));
  auto rect1 = std::make_shared<Rectangle<double>>(Point<double>(1, 1), 2, 2);

  figures.add(rect);
  figures.add(rect1);

  assert(figures.size() == 2);
  assert(static_cast<double>(*figures[0]) == 12.0);
  assert(static_cast<double>(*figures[1]) == 4.0);

  figures.printAll();
}

void testArrayWithSquares() {
  Array<std::shared_ptr<Square<double>>> squares;

  auto square1 = std::make_shared<Square<double>>(Point<double>(0, 0), 3);
  auto square2 = std::make_shared<Square<double>>(Point<double>(2, 2), 5);

  squares.add(square1);
  squares.add(square2);

  assert(squares.size() == 2);
  assert(static_cast<double>(*squares[0]) == 9.0);
  assert(static_cast<double>(*squares[1]) == 25.0);
  squares.printAll();
}

void testRemoveAndResize() {
  Array<std::shared_ptr<Square<double>>> squares;

  auto square1 = std::make_shared<Square<double>>(Point<double>(0, 0), 3);
  auto square2 = std::make_shared<Square<double>>(Point<double>(1, 1), 4);

  squares.add(square1);
  squares.add(square2);

  squares.removeAt(0);
  assert(squares.size() == 1);
  assert(static_cast<double>(*squares[0]) ==
         16.0);

  squares.printAll();
}

void testTotalArea() {
  Array<std::shared_ptr<Rectangle<double>>> figures;

  auto rect = std::make_shared<Rectangle<double>>(Point<double>(0, 0),
                                                  Point<double>(3, 2));
  auto rect1 = std::make_shared<Rectangle<double>>(Point<double>(2, 2), 2, 2);

  figures.add(rect);
  figures.add(rect1);

  double totalArea = figures.totalArea();
  assert(totalArea == 10.0);

  figures.printAll();
}

int main() {
  testArrayWithFigures();
  testArrayWithSquares();
  testRemoveAndResize();
  testTotalArea();

  std::cout << "All tests passed successfully.\n";
  return 0;
}
