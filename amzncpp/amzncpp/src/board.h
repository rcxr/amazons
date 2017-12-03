#pragma once
#include "tile.h"
#include "player.h"
#include "region.h"

class Board {
public:
  explicit Board(Tile* tiles, int width, int height);
  ~Board();

  int getWidth() const;
  int getHeight() const;
  int getSize() const;
  Tile get(int x, int y) const;

  int getScope(Player const& player) const;

private:
  static std::vector<Region*> processRegions(Board const* board, Tile* tiles);
  static void spreadRegion(Board const* board, bool* visited, Region* region, int x, int y);
  static int processScope(Board const* board, PlayerType playerType);
  static int getScope(Board const*, Tile tile, int x, int y);

  int index(int x, int y) const;
  bool isOutOfBoard(int x, int y) const;
  bool isPlayable(int x, int y) const;

  Tile const* const tiles;
  int const width;
  int const height;
  int const leftScope;
  int const rightScope;
  std::vector<Region*> regions;
};
