#pragma once
#include <vector>
#include "tile.h"

class Region {
public:
  explicit Region(int id);

  unsigned getCanonicalId() const;
  int getId() const;

  bool hasAmazons() const;
  bool hasBlanks() const;

  int getBlanks() const;

  void append(Tile tile, int x, int y);
  std::vector<std::pair<int, int>> const& getTilePositions() const;

  std::string toString() const;
  std::pair<int, int> getCanonicalDelta() const;

private:
  int const id;
  int minX;
  int minY;
  int blanks;
  int left;
  int right;
  std::vector<std::pair<int, int>> positions;
  std::vector<Tile> tiles;
};
