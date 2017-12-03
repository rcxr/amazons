#pragma once
#include <vector>

class Canonical {
public:
  static unsigned getId(std::vector<std::pair<int, int>> tiles);
  static std::string idToString(unsigned id);
  explicit Canonical(unsigned id, unsigned left, unsigned right);
  unsigned const id;
  unsigned const left;
  unsigned const right;
};
