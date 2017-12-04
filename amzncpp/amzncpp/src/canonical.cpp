#include <sstream>
#include <string>
#include "canonical.h"
#include "config.h"

int index(int x, int y) {
  return CANONICAL_COLS * x + y;
}

int index(std::pair<int, int> p) {
  return index(p.first, p.second);
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
  for (auto i = 0u; i < tiles.size(); ++i) {
    if (CANONICAL_ROWS <= positions[i].first || CANONICAL_COLS <= positions[i].second) {
      return CANONICAL_INVALID_ID;
    }
    id += getWeight(tiles[i], index(positions[i]));
  }
  return id;
}

std::string Canonical::idToString(unsigned id) {
  return CANONICAL_INVALID_ID == id ? "?" : std::to_string(id);
}

std::vector<Tile> Canonical::getTiles(unsigned id) {
  std::vector<Tile> tiles;
  for (auto i = 0; i < CANONICAL_ROWS * CANONICAL_COLS; ++i) {
    tiles.push_back(getTile(id & 3u));
    id = id >> 2;
  }
  return tiles;
}

bool Canonical::isValid(unsigned id) {
  auto tiles = getTiles(id);
  auto firstCol = false;
  auto firstRow = false;
  for (auto x = 0; x < CANONICAL_ROWS; ++x) {
    if (TILE_VOID != tiles[index(x, 0)]) {
      firstCol = true;
      break;
    }
  }
  for (auto y = 0; y < CANONICAL_COLS; ++y) {
    if (TILE_VOID != tiles[index(0, y)]) {
      firstRow = true;
      break;
    }
  }
  return firstCol && firstRow;
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
