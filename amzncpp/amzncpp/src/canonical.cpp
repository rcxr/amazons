#include <sstream>
#include <string>
#include "canonical.h"
#include "config.h"

int index(std::pair<int, int> p) {
  return p.first + p.second * CANONICAL_WIDTH;
}

Tile getTile(unsigned tile) {
  switch (tile) {
  case 1u: return TILE_BLANK;
  case 2u: return TILE_LEFT;
  case 3u: return TILE_RIGHT;
  default: return TILE_VOID;
  }
}

unsigned getWeight(Tile tile, int index) {
  unsigned weight;
  switch (tile) {
  case TILE_BLANK: weight = 1u; break;
  case TILE_LEFT: weight = 2u; break;
  case TILE_RIGHT: weight = 3u; break;
  default: weight = 0u; break;
  }
  return weight << index * 2;
}

unsigned Canonical::getId(std::vector<Tile> const& tiles, std::vector<std::pair<int, int>> const& positions) {
  auto id = 0u;
  for (auto i = 0; i < tiles.size(); ++i) {
    if (CANONICAL_WIDTH <= positions[i].first || CANONICAL_HEIGHT <= positions[i].second) {
      return CANONICAL_INVALID_ID;
    }
    id += getWeight(tiles[i], index(positions[i]));
  }
  return id;
}

std::string Canonical::idToString(unsigned id) {
  return CANONICAL_INVALID_ID == id ? "?" : std::to_string(id);
}

Tile* Canonical::getTiles(unsigned id) {
  auto tiles = new Tile[CANONICAL_WIDTH * CANONICAL_HEIGHT];
  for (auto i = 0; i < CANONICAL_WIDTH * CANONICAL_HEIGHT; ++i) {
    tiles[i] = getTile(id & 3u);
    id = id >> 2;
  }
  return tiles;
}

Canonical::Canonical(unsigned id, Move const* const leftMove, Move const* const rightMove) :
  id(id),
  leftMove(leftMove),
  rightMove(rightMove) {}

std::string Canonical::toString() const {
  std::ostringstream s;
  s << id << ' ' << (nullptr != leftMove) << ' ' << (nullptr != rightMove);
  if (leftMove) {
    s << ' ' << leftMove->toString();
  }
  if (rightMove) {
    s << ' ' << rightMove->toString();
  }
  return s.str();
}
