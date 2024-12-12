#include "squirrel.h"
#include "pegasus.h"
#include "knight.h"

Squirrel::Squirrel(int x, int y) : NPC(SquirrelType, x, y) {}
Squirrel::Squirrel(std::istream &is) : NPC(SquirrelType, is) {}

bool Squirrel::accept(std::shared_ptr<NPC> visitor) {
  return visitor->fight(
      std::shared_ptr<Squirrel>(this, [](Squirrel *) {}));
}

void Squirrel::print() { std::cout << *this; }

void Squirrel::save(std::ostream &os) {
  os << SquirrelType << std::endl;
  NPC::save(os);
}

bool Squirrel::fight(std::shared_ptr<Pegasus> other) {
  fight_notify(other, true);
  return true;
}

bool Squirrel::fight(std::shared_ptr<Knight> other) {
  fight_notify(other, false);
  return false;
}

bool Squirrel::fight(std::shared_ptr<Squirrel> other) {
  fight_notify(other, false);
  return false;
}

std::ostream &operator<<(std::ostream &os, Squirrel &knight) {
  os << "black knight: " << *static_cast<NPC *>(&knight) << std::endl;
  return os;
}