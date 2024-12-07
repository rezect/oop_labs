#include "knight.h"
#include "npc.h"
#include "pegasus.h"
#include "squirrel.h"

// Text Observer
class TextObserver : public IFightObserver {
private:
  TextObserver() {};

public:
  static std::shared_ptr<IFightObserver> get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
  }

  void on_fight(const std::shared_ptr<NPC> attacker,
                const std::shared_ptr<NPC> defender, bool win) override {
    if (win) {
      std::cout << std::endl << "Murder --------" << std::endl;
      attacker->print();
      defender->print();
    }
  }
};

// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream &is) {
  std::shared_ptr<NPC> result;
  int type{0};
  if (is >> type) {
    switch (type) {
    case PegasusType:
      result = std::make_shared<Pegasus>(is);
      break;
    case KnightType:
      result = std::make_shared<Knight>(is);
      break;
    case SquirrelType:
      result = std::make_shared<Squirrel>(is);
      break;
    }
  } else
    std::cerr << "unexpected NPC type:" << type << std::endl;

  if (result)
    result->subscribe(TextObserver::get());

  return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
  std::cout << "Type:" << (int)type << std::endl;
  std::shared_ptr<NPC> result;
  switch (type) {
  case PegasusType:
    result = std::make_shared<Pegasus>(x, y);
    break;
  case KnightType:
    result = std::make_shared<Knight>(x, y);
    break;
  case SquirrelType:
    result = std::make_shared<Squirrel>(x, y);
    break;
  default:
    break;
  }
  if (result)
    result->subscribe(TextObserver::get());

  return result;
}

// save array to file
void save(const set_t &array, const std::string &filename) {
  std::ofstream fs(filename);
  fs << array.size() << std::endl;
  for (auto &n : array)
    n->save(fs);
  fs.flush();
  fs.close();
}

set_t load(const std::string &filename) {
  set_t result;
  std::ifstream is(filename);
  if (is.good() && is.is_open()) {
    int count;
    is >> count;
    for (int i = 0; i < count; ++i)
      result.insert(factory(is));
    is.close();
  } else
    std::cerr << "Error: " << std::strerror(errno) << std::endl;
  return result;
}

// print to screen
std::ostream &operator<<(std::ostream &os, const set_t &array) {
  for (auto &n : array)
    n->print();
  return os;
}

set_t fight(const set_t &array, size_t distance) {
  set_t dead_list;

  for (const auto &attacker : array)
    for (const auto &defender : array)
      if ((attacker != defender) && (attacker->is_close(defender, distance))) {
        bool success{false};
        if (defender->is_pegasus())
          success =
              attacker->fight(std::dynamic_pointer_cast<Pegasus>(defender));
        if (defender->is_knight())
          success =
              attacker->fight(std::dynamic_pointer_cast<Knight>(defender));
        if (defender->is_squirrel())
          success =
              attacker->fight(std::dynamic_pointer_cast<Squirrel>(defender));
        if (success)
          dead_list.insert(defender);
      }

  return dead_list;
}

int main() {
  set_t array; // монстры

  // Гененрируем начальное распределение монстров
  std::cout << "Generating ..." << std::endl;
  for (size_t i = 0; i < 100; ++i)
    array.insert(factory(NpcType(std::rand() % 3 + 1), std::rand() % 100,
                         std::rand() % 100));
  std::cout << "Saving ..." << std::endl;

  save(array, "npc.txt");

  std::cout << "Loading ..." << std::endl;
  array = load("npc.txt");

  std::cout << "Fighting ..." << std::endl << array;

  for (size_t distance = 20; (distance <= 100) && !array.empty();
       distance += 10) {
    auto dead_list = fight(array, distance);
    for (auto &d : dead_list)
      array.erase(d);
    std::cout << "Fight stats ----------" << std::endl
              << "distance: " << distance << std::endl
              << "killed: " << dead_list.size() << std::endl
              << std::endl
              << std::endl;
  }

  std::cout << "Survivors:" << array;

  return 0;
}