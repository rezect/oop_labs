#include "knight.h"
#include "squirrel.h"
#include "pegasus.h"

Knight::Knight(int x, int y) : NPC(KnightType, x, y) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

void Knight::print() { std::cout << *this; }

bool Knight::accept(std::shared_ptr<NPC> visitor) {
  return visitor->fight(std::shared_ptr<Knight>(this, [](Knight *) {}));
}

void Knight::save(std::ostream &os) {
  os << KnightType << std::endl;
  NPC::save(os);
}

bool Knight::fight(std::shared_ptr<Pegasus> other) {
  fight_notify(other, false);
  return false;
}

bool Knight::fight(std::shared_ptr<Knight> other) {
  fight_notify(other, false);
  return false;
}

bool Knight::fight(std::shared_ptr<Squirrel> other) {
  fight_notify(other, true);
  return true;
}

std::ostream &operator<<(std::ostream &os, Knight &knight) {
  os << "knight: " << *static_cast<NPC *>(&knight) << std::endl;
  return os;
}