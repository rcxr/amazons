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
