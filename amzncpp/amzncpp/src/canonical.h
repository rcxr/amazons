#pragma once
#include <vector>
#include "move.h"

class Canonical {
public:
  static unsigned getId(std::vector<Tile> const& tiles, std::vector<std::pair<int, int>> const& positions);
  static std::string idToString(unsigned id);

  Canonical(unsigned id, unsigned leftId, unsigned rightId, Move const* const leftMove, Move const* const rightMove);

  unsigned const id;
  unsigned const leftId;
  unsigned const rightId;
  Move const* const leftMove;
  Move const* const rightMove;
};
