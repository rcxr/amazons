#include "canonical.h"
#include "math.h"
#include "config.h"
#include <string>

int index(std::pair<int, int> p) {
  return CANONICAL_HEIGHT * p.first + p.second;
}

unsigned Canonical::getId(std::vector<std::pair<int, int>> tiles) {
  auto id = 0u;
  for (auto tile : tiles) {
    if (CANONICAL_WIDTH <= tile.first || CANONICAL_HEIGHT <= tile.second) {
      return CANONICAL_INVALID_ID;
    }
    id += Math::powOf3(index(tile));
  }
  return id;
}

std::string Canonical::idToString(unsigned id) {
  return CANONICAL_INVALID_ID == id ? "?" : std::to_string(id);
}

Canonical::Canonical(unsigned id, unsigned left, unsigned right) : id(id), left(left), right(right) {}
