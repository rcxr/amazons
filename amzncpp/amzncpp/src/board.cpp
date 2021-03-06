#include "board.h"
#include "canonical.h"
#include "config.h"

Board::Board(std::vector<Tile> const& tiles, int rows, int cols) :
  tiles(tiles),
  rows(rows),
  cols(cols),
  leftScope(processScope(this, Player::instanceLeft())),
  rightScope(processScope(this, Player::instanceRight())),
  regions(processRegions(this, tiles)) {
  for (auto region : regions) {
    if (!region->hasAmazons()) {
      for (auto& tile : region->getTilePositions()) {
        this->tiles[index(tile.first, tile.second)] = TILE_OUT_OF_REACH;
      }
    }
  }
}

Board::Board(unsigned id) : Board(Canonical::getTiles(id), CANONICAL_ROWS, CANONICAL_COLS) {}

Board::~Board() {
  for (auto region : regions) {
    delete region;
  }
}

std::vector<Region*> const& Board::getAllRegions() const {
  return regions;
}

std::vector<Region*> Board::getPlayableRegions() const {
  std::vector<Region*> playableRegions;
  for (auto region : regions) {
    if (region->hasAmazons() && region->hasBlanks()) {
      playableRegions.push_back(region);
    }
  }
  return playableRegions;
}

int Board::getRows() const {
  return rows;
}

int Board::getCols() const {
  return cols;
}

int Board::getSize() const {
  return rows * cols;
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

std::vector<Move*> Board::getMoves(Player const& player) const {
  std::vector<Move*> moves;
  for (auto x = 0; x < rows; ++x) {
    for (auto y = 0; y < cols; ++y) {
      appendMoves(moves, player, x, y);
    }
  }
  return moves;
}

void Board::appendMoves(std::vector<Move*>& moves, Player const& player, int fromX, int fromY) const {
  if (player.getTile() != get(fromX, fromY)) {
    return;
  }
  for (auto i = 1; TILE_BLANK == get(fromX - i, fromY - i); ++i) { appendMoves(moves, player, fromX, fromY, fromX - i, fromY - i); }
  for (auto i = 1; TILE_BLANK == get(fromX - i, fromY + i); ++i) { appendMoves(moves, player, fromX, fromY, fromX - i, fromY + i); }
  for (auto i = 1; TILE_BLANK == get(fromX + i, fromY - i); ++i) { appendMoves(moves, player, fromX, fromY, fromX + i, fromY - i); }
  for (auto i = 1; TILE_BLANK == get(fromX + i, fromY + i); ++i) { appendMoves(moves, player, fromX, fromY, fromX + i, fromY + i); }
  for (auto i = 1; TILE_BLANK == get(fromX - i, fromY); ++i) { appendMoves(moves, player, fromX, fromY, fromX - i, fromY); }
  for (auto i = 1; TILE_BLANK == get(fromX + i, fromY); ++i) { appendMoves(moves, player, fromX, fromY, fromX + i, fromY); }
  for (auto i = 1; TILE_BLANK == get(fromX, fromY - i); ++i) { appendMoves(moves, player, fromX, fromY, fromX, fromY - i); }
  for (auto i = 1; TILE_BLANK == get(fromX, fromY + i); ++i) { appendMoves(moves, player, fromX, fromY, fromX, fromY + i); }
}

void Board::appendMoves(std::vector<Move*>& moves, Player const& player, int fromX, int fromY, int toX, int toY) const {
  for (auto i = 1; fromX == toX - i && fromY == toY - i || TILE_BLANK == get(toX - i, toY - i); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX - i, toY - i));
  }
  for (auto i = 1; fromX == toX - i && fromY == toY + i || TILE_BLANK == get(toX - i, toY + i); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX - i, toY + i));
  }
  for (auto i = 1; fromX == toX + i && fromY == toY - i || TILE_BLANK == get(toX + i, toY - i); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX + i, toY - i));
  }
  for (auto i = 1; fromX == toX + i && fromY == toY + i || TILE_BLANK == get(toX + i, toY + i); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX + i, toY + i));
  }
  for (auto i = 1; fromX == toX - i && fromY == toY || TILE_BLANK == get(toX - i, toY); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX - i, toY));
  }
  for (auto i = 1; fromX == toX + i && fromY == toY || TILE_BLANK == get(toX + i, toY); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX + i, toY));
  }
  for (auto i = 1; fromX == toX && fromY == toY - i || TILE_BLANK == get(toX, toY - i); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX, toY - i));
  }
  for (auto i = 1; fromX == toX && fromY == toY + i || TILE_BLANK == get(toX, toY + i); ++i) {
    moves.push_back(new Move(player, fromX, fromY, toX, toY, toX, toY + i));
  }
}

Board* Board::apply(Move const* move) const {
  auto newTiles = this->tiles;
  newTiles[index(move->getFrom())] = TILE_BLANK;
  newTiles[index(move->getTo())] = move->getPlayer().getTile();
  newTiles[index(move->getTarget())] = TILE_VOID;
  return new Board(newTiles, rows, cols);
}

bool Board::isLegalMove(Move const* move) const {
  return move && move->getFrom() != move->getTo()
    && move->getTo() != move->getTarget()
    && move->getPlayer().getTile() == get(move->getFrom())
    && isClear(move->getFromX(), move->getFromY(), move->getToX(), move->getToY(), move->getFromX(), move->getFromY())
    && isClear(move->getToX(), move->getToY(), move->getTargetX(), move->getTargetY(), move->getFromX(), move->getFromY());
}

std::vector<Region*> Board::processRegions(Board const* board, std::vector<Tile> const& tiles) {
  int id = 0;
  std::vector<Region*> regions;
  auto visited = new bool[board->getSize()];
  std::fill(visited, visited + board->getSize(), false);
  for (auto x = 0; x < board->rows; ++x) {
    for (auto y = 0; y < board->cols; ++y) {
      if (!visited[board->index(x, y)] && board->isPlayable(x, y)) {
        auto region = new Region(++id);
        spreadRegion(board, visited, region, x, y);
        regions.push_back(region);
      }
    }
  }
  delete[] visited;
  return regions;
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

int Board::processScope(Board const* board, Player const& player) {
  auto scope = 0;
  for (auto x = 0; x < board->rows; ++x) {
    for (auto y = 0; y < board->cols; ++y) {
      scope += getScope(board, player.getTile(), x, y);
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
  return cols * x + y;
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
  return x < 0 || rows <= x || y < 0 || cols <= y;
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
