#include <iostream>
#include "log.h"
#include "config.h"

bool isEven(int x, int y) { return 0 == (x + y) % 2; }

char tileToFirstChar(Tile tile, bool even) {
  switch (tile) {
  case TILE_BLANK: return even ? CHAR_BLANK_EVEN : CHAR_BLANK_ODD;
  case TILE_LEFT: return CHAR_LEFT_1;
  case TILE_RIGHT: return CHAR_RIGHT_1;
  case TILE_VOID: return CHAR_VOID;
  case TILE_OUT_OF_BOARD: return CHAR_OUT_OF_BOARD;
  case TILE_OUT_OF_REACH: return even ? CHAR_OUT_OF_REACH_EVEN : CHAR_OUT_OF_REACH_ODD;
  default: throw;
  }
}

char tileToSecondChar(Tile tile, bool even) {
  switch (tile) {
  case TILE_BLANK: return even ? CHAR_BLANK_EVEN : CHAR_BLANK_ODD;
  case TILE_LEFT: return CHAR_LEFT_2;
  case TILE_RIGHT: return CHAR_RIGHT_2;
  case TILE_VOID: return CHAR_VOID;
  case TILE_OUT_OF_BOARD: return CHAR_OUT_OF_BOARD;
  case TILE_OUT_OF_REACH: return even ? CHAR_OUT_OF_REACH_EVEN : CHAR_OUT_OF_REACH_ODD;
  default: throw;
  }
}

void Log::error(std::string const& message) {
  std::cout << "ERROR: " << message << std::endl;
}

void Log::info(std::string const& message) {
  std::cout << message << std::endl;
}

void Log::info(Board const* board) {
  for (auto x = -1; x <= board->getWidth(); ++x) {
    for (auto y = -1; y <= board->getHeight(); ++y) {
      std::cout << tileToFirstChar(board->get(x, y), isEven(x, y)) << tileToSecondChar(board->get(x, y), isEven(x, y));
    }
    std::cout << std::endl;
  }
}
