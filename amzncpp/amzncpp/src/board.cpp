#include "board.h"
#include <unordered_map>
#include <algorithm>

Board::Board(Tile* tiles, int width, int height) :
  tiles(tiles),
  width(width),
  height(height),
  leftScope(processScope(this, PLAYER_TYPE_LEFT)),
  rightScope(processScope(this, PLAYER_TYPE_RIGHT)),
  regions(processRegions(this, tiles)) {}

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

Tile Board::get(std::pair<int, int> const& p) const {
  return get(p.first, p.second);
}

int Board::getLeftScope() const {
  return getScope(Player::instanceLeft());
}

int Board::getRightScope() const {
  return getScope(Player::instanceRight());
}

int Board::getScope(Player const& player) const {
  return player.isLeft() ? leftScope : rightScope;
}

Board* Board::apply(Move const* move) const {
  auto tiles = new Tile[width * height];
  memcpy(tiles, this->tiles, width * height * sizeof Tile);
  tiles[index(move->getFrom())] = TILE_BLANK;
  tiles[index(move->getTo())] = move->getPlayer().getTile();
  tiles[index(move->getTarget())] = TILE_VOID;
  return new Board(tiles, width, height);
}

bool Board::isLegalMove(Move const* move) const {
  return move && move->getFrom() != move->getTo()
    && move->getTo() != move->getTarget()
    && move->getPlayer().getTile() == get(move->getFrom())
    && isClear(move->getFromX(), move->getFromY(), move->getToX(), move->getToY(), move->getFromX(), move->getFromY())
    && isClear(move->getToX(), move->getToY(), move->getTargetX(), move->getTargetY(), move->getFromX(), move->getFromY());
}

std::vector<Region*> Board::processRegions(Board const* board, Tile* tiles) {
  int id = 0;
  std::vector<Region*> regions;
  auto visited = new bool[board->getSize()];
  std::fill(visited, visited + board->getSize(), false);
  for (auto x = 0; x < board->width; ++x) {
    for (auto y = 0; y < board->height; ++y) {
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

int Board::processScope(Board const* board, PlayerType playerType) {
  auto scope = 0;
  for (auto x = 0; x < board->width; ++x) {
    for (auto y = 0; y < board->height; ++y) {
      scope += getScope(board, Player::instance(playerType).getTile(), x, y);
    }
  }
  return scope;
}

int Board::getScope(Board const* board, Tile tile, int x, int y) {
  if (tile != board->get(x, y)) {
    return 0;
  }
  auto scope = 0;
  for (auto i = 1; TILE_BLANK == board->get(x - i, y - i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x - i, y + i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x + i, y - i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x + i, y + i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x - i, y); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x + i, y); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x, y - i); ++i) { ++scope; }
  for (auto i = 1; TILE_BLANK == board->get(x, y + i); ++i) { ++scope; }
  return scope;
}

int Board::index(int x, int y) const {
  return height * x + y;
}

int Board::index(std::pair<int, int> const& p) const {
  return index(p.first, p.second);
}

bool Board::isClear(int fromX, int fromY, int toX, int toY, int skipX, int skipY) const {
  int dX = fromX - toX;
  int dY = fromY - toY;
  if (dX && dY && abs(dX) != abs(dY)) {
    return false;
  }
  int stepX = dX < 0 ? -1 : 0 < dX ? 1 : 0;
  int stepY = dY < 0 ? -1 : 0 < dY ? 1 : 0;
  while (toX != fromX || toY != fromY) {
    if ((toX != skipX || toY != skipY) && TILE_BLANK != get(toX, toY)) {
      return false;
    }
    toX += stepX;
    toY += stepY;
  }
  return true;
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
