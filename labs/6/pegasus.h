#pragma once
#include "npc.h"

struct Pegasus : public NPC {
  Pegasus(int x, int y);
  Pegasus(std::istream &is);

  void print() override;

  bool is_pegasus() const override;

  bool fight(std::shared_ptr<Pegasus> other) override;
  bool fight(std::shared_ptr<Knight> other) override;
  bool fight(std::shared_ptr<Squirrel> other) override;

  void save(std::ostream &os) override;

  friend std::ostream &operator<<(std::ostream &os, Pegasus &pegasus);
};