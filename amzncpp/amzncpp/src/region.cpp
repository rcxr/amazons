#include "region.h"

Region::Region(int id) : id(id), blanks(0), left(0), right(0) {}

bool Region::hasAmazons() const {
  return 0 < left + right;
}

bool Region::hasBlanks() const {
  return 0 < blanks;
}

void Region::append(Tile tile, int x, int y) {
  switch (tile) {
  case TILE_BLANK:
    ++blanks;
    break;
  case TILE_LEFT:
    ++left;
    break;
  case TILE_RIGHT:
    ++right;
    break;
  default:
    throw;
  }
  tiles.push_back(std::make_pair(x, y));
}

std::vector<std::pair<int, int>> const& Region::getTiles() const {
  return tiles;
}
