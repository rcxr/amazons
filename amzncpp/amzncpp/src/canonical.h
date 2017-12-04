#pragma once
#include <vector>
#include "move.h"

class Canonical {
public:
  static unsigned getId(std::vector<Tile> const& tiles, std::vector<std::pair<int, int>> const& positions);
  static std::string idToString(unsigned id);
  static std::vector<Tile> getTiles(unsigned id);
  static bool isValid(unsigned id);
  static unsigned negative(unsigned id);

  Canonical(unsigned id, Move const* const leftMove, Move const* const rightMove);

  Canonical* negative() const;

  std::string toString() const;

  unsigned const id;
  Move const* const leftMove;
  Move const* const rightMove;
};
