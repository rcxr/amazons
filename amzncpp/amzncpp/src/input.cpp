#include <iostream>
#include <fstream>
#include "input.h"
#include "log.h"
#include "config.h"
#include "turn.h"

Tile intToTile(int tile) {
  switch (tile) {
  case 0: return TILE_BLANK;
  case 1: return TILE_LEFT;
  case 2: return TILE_RIGHT;
  case 3: return TILE_VOID;
  default: throw;
  }
}

Board* parseFile(std::string const& filename) {
  std::ifstream stream(filename);
  if (!stream.is_open()) {
    Log::error("File could not be opened");
    return nullptr;
  }

  int width;
  int height;
  int tile;
  stream >> tile;
  if (tile < 1) {
    stream >> width >> height;
    // We consumed metadata, we need to consume first actual value
    stream >> tile;
  }
  else {
    // Value is an actual value, dimensions are as default
    width = BOARD_DEFAULT_WIDTH;
    height = BOARD_DEFAULT_HEIGHT;
  }

  // Creating dynamic array and setting first position that we already got
  Tile* tiles = new Tile[width * height];
  tiles[0] = intToTile(tile);

  for (auto i = 1; i < width * height; ++i) {
    stream >> tile;
    tiles[i] = intToTile(tile);
  }
  stream.close();

  Log::info("Board successfully loaded from file");
  return new Board(tiles, width, height);
}

std::string getFile() {
  Log::info("Choose a file");
  std::string filename;
  std::cin >> filename;
  return filename;
}

Board* Input::getBoard() {
  Board* board = nullptr;
  while (!board) {
    board = parseFile(getFile());
  }
  return board;
}

Player const& Input::getPlayer() {
  while (true) {
    Log::info("Choose player (left or right)");
    std::string player;
    std::cin >> player;
    if (0 == player.compare("left") || 0 == player.compare("l")) {
      return Player::instanceLeft();
    }
    if (0 == player.compare("right") || 0 == player.compare("r")) {
      return Player::instanceRight();
    }
  }
}

bool Input::getRetry() {
  while (true) {
    Log::info("Would you like to play again?");
    std::string in;
    std::cin >> in;
    if (0 == in.compare("yes") || 0 == in.compare("y")) {
      return true;
    }
    if (0 == in.compare("no") || 0 == in.compare("n")) {
      return false;
    }
  }
}

Move* getMove(Player const& player) {
  Log::info("Make a move for " + player.getLabel() + " (\"fromRow fromCol toRow toCol targetRow targetCol\")");
  int fromX, fromY, toX, toY, targetX, targetY;
  std::cin >> fromX >> fromY >> toX >> toY >> targetX >> targetY;
  return new Move(player, fromX, fromY, toX, toY, targetX, targetY);
}

Move* Input::getMove(Board const* board, Player const& player) {
  Move* move = getMove(player);
  while (!board->isLegalMove(move)) {
    Log::error("That is not a valid move");
    move = getMove(player);
  }
  return move;
}

CalculatorHeuristic Input::getMinMax() {
  while (true) {
    Log::info("Choose heuristic (minmax or maxmin)");
    std::string h;
    std::cin >> h;
    if (0 == h.compare("min") || 0 == h.compare("minmax")) {
      return CALCULATOR_HEURISTIC_MINMAX;
    }
    if (0 == h.compare("max") || 0 == h.compare("maxmin")) {
      return CALCULATOR_HEURISTIC_MAXMIN;
    }
  }
}
