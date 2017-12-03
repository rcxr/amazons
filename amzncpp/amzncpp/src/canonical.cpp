#include "canonical.h"
#include "config.h"
#include <string>

int index(std::pair<int, int> p) {
  return p.first + p.second * CANONICAL_WIDTH;
}

unsigned getWeight(Tile tile, int index) {
  unsigned weight;
  switch (tile) {

  case TILE_BLANK: weight = 3u;
  case TILE_LEFT: weight = 2u;
  case TILE_RIGHT: weight = 1u;
  default: weight = 0u;
  }
  return weight << (index * 2);
}

unsigned Canonical::getId(std::vector<Tile> const& tiles, std::vector<std::pair<int, int>> const& positions) {
  auto id = UINT_MAX;
  for (auto i = 0; i < tiles.size(); ++i) {
    if (CANONICAL_WIDTH <= positions[i].first || CANONICAL_HEIGHT <= positions[i].second) {
      return CANONICAL_INVALID_ID;
    }
    id = id ^ getWeight(tiles[i], index(positions[i]));
  }
  return id;
}

std::string Canonical::idToString(unsigned id) {
  return CANONICAL_INVALID_ID == id ? "?" : std::to_string(id);
}

Canonical::Canonical(unsigned id, unsigned leftId, unsigned rightId, Move const* const leftMove, Move const* const rightMove):
  id(id),
  leftId(leftId),
  rightId(rightId),
  leftMove(leftMove),
  rightMove(rightMove) {}
