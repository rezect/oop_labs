#pragma once
#include "npc.h"

struct Squirrel : public NPC {
  Squirrel(int x, int y);
  Squirrel(std::istream &is);

  void print() override;
  void save(std::ostream &os) override;
  bool is_squirrel() const override;

  bool fight(std::shared_ptr<Pegasus> other) override;
  bool fight(std::shared_ptr<Knight> other) override;
  bool fight(std::shared_ptr<Squirrel> other) override;
  friend std::ostream &operator<<(std::ostream &os, Squirrel &squirrel);
};