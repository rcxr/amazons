#pragma once
#include "tile.h"
#include "player.h"
#include "region.h"
#include "move.h"

class Board {
public:
  explicit Board(Tile* tiles, int width, int height);
  explicit Board(unsigned id);
  ~Board();

  std::vector<Region*> const& getRegions() const;

  int getWidth() const;
  int getHeight() const;
  int getSize() const;
  Tile get(int x, int y) const;
  Tile get(std::pair<int, int> const& p) const;

  int getLeftScope() const;
  int getRightScope() const;
  int getScope(Player const& player) const;

  std::vector<Move*> getMoves(Player const&) const;
  Board* apply(Move const* move) const;
  bool isLegalMove(Move const* move) const;

private:
  static std::vector<Region*> processRegions(Board const* board, Tile* tiles);
  static void spreadRegion(Board const* board, bool* visited, Region* region, int x, int y);
  static int processScope(Board const* board, Player const& player);
  static int getScope(Board const*, Tile tile, int x, int y);

  void appendMoves(std::vector<Move*>& moves, Player const& player, int fromX, int fromY) const;
  void appendMoves(std::vector<Move*>& moves, Player const& player, int fromX, int fromY, int toX, int toY) const;

  int index(int x, int y) const;
  int index(std::pair<int, int> const& p) const;
  bool isClear(int fromX, int fromY, int toX, int toY, int skipX, int skipY) const;
  bool isOutOfBoard(int x, int y) const;
  bool isPlayable(int x, int y) const;

  Tile const* const tiles;
  int const width;
  int const height;
  int const leftScope;
  int const rightScope;
  std::vector<Region*> regions;
};
