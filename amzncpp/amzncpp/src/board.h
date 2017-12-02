#pragma once
#include "tile.h"
#include "player.h"

class Board {
public:
  explicit Board(Tile const* board, int width, int height);
  ~Board();

  int getWidth() const;
  int getHeight() const;
  Tile get(int x, int y) const;

  int getScope(Player const* player) const;

private:
  int getScope(Tile tile, int x, int y) const;
  int index(int x, int y) const;
  bool isOutOfBounds(int x, int y) const;

  int const width;
  int const height;
  Tile const* const board;
};
