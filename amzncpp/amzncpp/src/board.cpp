#include "board.h"

Board::Board(Tile const* board, int width, int height) : width(width), height(height), board(board) {}
Board::~Board() {
  delete[] board;
}

int Board::getWidth() const {
  return width;
}

int Board::getHeight() const {
  return height;
}

Tile Board::get(int x, int y) const {
  if (isOutOfBounds(x, y)) {
    return TILE_OUT_OF_BOUNDS;
  }
  return board[index(x, y)];
}

int Board::getScope(Player const* player) const {
  auto scope = 0;
  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      scope += getScope(player->getTile(), x, y);
    }
  }
  return scope;
}

int Board::getScope(Tile tile, int x, int y) const {
  if (tile != get(x, y)) {
    return 0;
  }
  auto scope = 0;
  for (auto i = 1; TILE_BLANK == get(x - i, y - i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x - i, y + i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x + i, y - i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x + i, y + i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x - i, y); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x + i, y); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x, y - i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == get(x, y + i); ++i) { ++scope; }
  return scope;
}

int Board::index(int x, int y) const {
  return height * x + y;
}

bool Board::isOutOfBounds(int x, int y) const {
  return x < 0 || width <= x || y < 0 || height <= y;
}
