#include "region.h"
#include "canonical.h"
#include <string>

Region::Region(int id) : id(id), minX(0), minY(0), blanks(0), left(0), right(0) {}

unsigned Region::getCanonicalId() const {
  std::vector<std::pair<int, int>> positions;
  for (auto p : this->positions) {
    positions.push_back(std::make_pair(p.first - minX, p.second - minY));
  }
  return Canonical::getId(tiles, positions);
}

int Region::getId() const { return id; }

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
  minX = minX < x ? minX : x;
  minY = minY < y ? minY : y;
  positions.push_back(std::make_pair(x, y));
  tiles.push_back(tile);
}

std::vector<std::pair<int, int>> const& Region::getTilePositions() const {
  return positions;
}

std::string Region::toString() const {
  return "Region (id: "
    + std::to_string(id)
    + ", canonical: "
    + Canonical::idToString(getCanonicalId())
    + ", left/right/blanks: "
    + std::to_string(left)
    + "/" + std::to_string(right)
    + "/" + std::to_string(blanks)
    + ")";
}
