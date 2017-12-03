#pragma once
#include <vector>
#include "tile.h"

class Region {
public:
  explicit Region(int id);

  bool hasAmazons() const;
  bool hasBlanks() const;

  void append(Tile tile, int x, int y);
  std::vector<std::pair<int, int>> const& getTiles() const;

private:
  int id;
  int blanks;
  int left;
  int right;
  std::vector<std::pair<int, int>> tiles;
};
