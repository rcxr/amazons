#include <string>
#include <sstream>
#include "region.h"
#include "canonical.h"

Region::Region(int id) : id(id), minX(INT_MAX), minY(INT_MAX), blanks(0), left(0), right(0) {}

unsigned Region::getCanonicalId() const {
  std::vector<std::pair<int, int>> canonicalPositions;
  for (auto p : positions) {
    canonicalPositions.push_back(std::make_pair(p.first - minX, p.second - minY));
  }
  return Canonical::getId(tiles, canonicalPositions);
}

int Region::getId() const { return id; }

bool Region::hasAmazons() const {
  return 0 < left + right;
}

bool Region::hasBlanks() const {
  return 0 < blanks;
}

int Region::getBlanks() const {
  return blanks;
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
  std::ostringstream s;
  s <<
    "Region (id: " <<
    id <<
    ", canonical: " <<
    Canonical::idToString(getCanonicalId()) <<
    ", left/right/blanks: " <<
    left << '/' << right << '/' << blanks <<
    ')';
  return s.str();
}
