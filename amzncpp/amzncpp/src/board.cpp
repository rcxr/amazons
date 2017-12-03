#include "board.h"
#include <unordered_map>
#include <algorithm>

Board::Board(Tile* tiles, int width, int height) : tiles(tiles), width(width), height(height), regions(processRegions(this, tiles)) {}

Board::~Board() {
  for (auto region : regions) {
    delete region;
  }
  delete[] tiles;
}

int Board::getWidth() const {
  return width;
}

int Board::getHeight() const {
  return height;
}

int Board::getSize() const {
  return width * height;
}

Tile Board::get(int x, int y) const {
  if (isOutOfBoard(x, y)) {
    return TILE_OUT_OF_BOARD;
  }
  return tiles[index(x, y)];
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

std::vector<Region*> Board::processRegions(Board const* board, Tile* tiles) {
  int id = 0;
  std::vector<Region*> regions;
  auto visited = new bool[board->getSize()];
  std::fill(visited, visited + board->getSize(), false);
  for (auto x = 0; x < board->getWidth(); ++x) {
    for (auto y = 0; y < board->getHeight(); ++y) {
      if (!visited[board->index(x, y)] && board->isPlayable(x, y)) {
        auto region = new Region(++id);
        spreadRegion(board, visited, region, x, y);
        regions.push_back(region);
      }
    }
  }
  delete[] visited;

  std::vector<Region*> filteredRegions;
  for (auto region : regions) {
    if (!region->hasAmazons()) {
      for (auto& tile : region->getTiles()) {
        tiles[board->index(tile.first, tile.second)] = TILE_OUT_OF_REACH;
      }
    }
    else if (region->hasBlanks()) {
      filteredRegions.push_back(region);
    }
  }

  return filteredRegions;
}

void Board::spreadRegion(Board const* board, bool* visited, Region* region, int x, int y) {
  if (!board->isPlayable(x, y) || visited[board->index(x, y)]) {
    return;
  }
  visited[board->index(x, y)] = true;
  region->append(board->get(x, y), x, y);
  spreadRegion(board, visited, region, x + 1, y + 1);
  spreadRegion(board, visited, region, x - 1, y - 1);
  spreadRegion(board, visited, region, x + 1, y - 1);
  spreadRegion(board, visited, region, x - 1, y + 1);
  spreadRegion(board, visited, region, x + 1, y);
  spreadRegion(board, visited, region, x - 1, y);
  spreadRegion(board, visited, region, x, y - 1);
  spreadRegion(board, visited, region, x, y + 1);
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

bool Board::isOutOfBoard(int x, int y) const {
  return x < 0 || width <= x || y < 0 || height <= y;
}

bool Board::isPlayable(int x, int y) const {
  switch (get(x, y)) {
  case TILE_BLANK:
  case TILE_LEFT:
  case TILE_RIGHT:
    return true;
  default:
    return false;
  }
}
