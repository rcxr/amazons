#include <iostream>
#include <fstream>
#include "input.h"
#include "log.h"
#include "config.h"

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

  int tile;
  auto tiles = new Tile[BOARD_DEFAULT_WIDTH * BOARD_DEFAULT_HEIGHT];
  for (auto i = 0; i < BOARD_DEFAULT_WIDTH * BOARD_DEFAULT_HEIGHT; ++i) {
    stream >> tile;
    tiles[i] = intToTile(tile);
  }
  stream.close();

  auto board = new Board(tiles, BOARD_DEFAULT_WIDTH, BOARD_DEFAULT_HEIGHT);
  Log::info("Board successfully loaded from file");
  Log::info(board);
  return board;
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

Move* Input::getMove(Player const& player) {
  Log::info("Make a move for " + player.getLabel());
  Log::info("You need to type six numbers");
  Log::info("Two numbers for the row and column of the amazon you want to use");
  Log::info("Two numbers for the row and column of the destination tile");
  Log::info("Two numbers for the row and column of the tile the amazon will shoot");
  int fromX, fromY, toX, toY, targetX, targetY;
  std::cin >> fromX >> fromY >> toX >> toY >> targetX >> targetY;
  return new Move(player, fromX, fromY, toX, toY, targetX, targetY);
}
