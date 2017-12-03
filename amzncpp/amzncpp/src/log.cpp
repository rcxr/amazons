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

void Log::clear() {
#ifdef _WIN32
  system("cls");
#else
  // Assume POSIX
  system("clear");
#endif
}

void Log::title(std::string const& title) {
  info("===[ " + title + " ]===");
}

void Log::info(std::string const& message) {
  std::cout << message << std::endl;
}

void Log::info(Board const* board) {
  title("Stats");
  std::cout << "  Left scope = " << board->getLeftScope() << ",  Right scope = " << board->getRightScope() << std::endl;
  info(board->getRegions());
  title("Board");
  std::cout << "  Left        >   " << tileToFirstChar(TILE_LEFT, true) << tileToSecondChar(TILE_LEFT, true) << "  ";
  std::cout << "  Right       >   " << tileToFirstChar(TILE_RIGHT, true) << tileToSecondChar(TILE_RIGHT, true) << std::endl;
  std::cout << "                " << tileToFirstChar(TILE_BLANK, true) << tileToSecondChar(TILE_BLANK, true) << tileToFirstChar(TILE_BLANK, false) << tileToSecondChar(TILE_BLANK, false) << tileToFirstChar(TILE_BLANK, true) << tileToSecondChar(TILE_BLANK, true);
  std::cout << "                " << tileToFirstChar(TILE_OUT_OF_REACH, true) << tileToSecondChar(TILE_OUT_OF_REACH, true) << tileToFirstChar(TILE_OUT_OF_REACH, false) << tileToSecondChar(TILE_OUT_OF_REACH, false) << tileToFirstChar(TILE_OUT_OF_REACH, true) << tileToSecondChar(TILE_OUT_OF_REACH, true) << std::endl;
  std::cout << "  Blanks      > " << tileToFirstChar(TILE_BLANK, false) << tileToSecondChar(TILE_BLANK, false) << tileToFirstChar(TILE_BLANK, true) << tileToSecondChar(TILE_BLANK, true) << tileToFirstChar(TILE_BLANK, false) << tileToSecondChar(TILE_BLANK, false);
  std::cout << "  Unreachable > " << tileToFirstChar(TILE_OUT_OF_REACH, false) << tileToSecondChar(TILE_OUT_OF_REACH, false) << tileToFirstChar(TILE_OUT_OF_REACH, true) << tileToSecondChar(TILE_OUT_OF_REACH, true) << tileToFirstChar(TILE_OUT_OF_REACH, false) << tileToSecondChar(TILE_OUT_OF_REACH, false) << std::endl;
  std::cout << "                " << tileToFirstChar(TILE_BLANK, true) << tileToSecondChar(TILE_BLANK, true) << tileToFirstChar(TILE_BLANK, false) << tileToSecondChar(TILE_BLANK, false) << tileToFirstChar(TILE_BLANK, true) << tileToSecondChar(TILE_BLANK, true);
  std::cout << "                " << tileToFirstChar(TILE_OUT_OF_REACH, true) << tileToSecondChar(TILE_OUT_OF_REACH, true) << tileToFirstChar(TILE_OUT_OF_REACH, false) << tileToSecondChar(TILE_OUT_OF_REACH, false) << tileToFirstChar(TILE_OUT_OF_REACH, true) << tileToSecondChar(TILE_OUT_OF_REACH, true) << std::endl;
  for (auto x = -1; x <= board->getWidth(); ++x) {
    for (auto y = -1; y <= board->getHeight(); ++y) {
      std::cout << tileToFirstChar(board->get(x, y), isEven(x, y)) << tileToSecondChar(board->get(x, y), isEven(x, y));
    }
    std::cout << std::endl;
  }
}

void Log::info(std::vector<Region*> const& regions) {
  title("Nonzero games (" + std::to_string(regions.size()) + ")");
  for (auto region : regions) {
    std::cout << region->toString() << std::endl;
  }
}

void Log::info(std::string const& label, std::pair<Move*, Board*> move) {
  title(label);
  std::cout << "  Left scope = " << move.second->getLeftScope() << ",  Right scope = " << move.second->getRightScope() << std::endl;
  std::cout << "  From = (" << move.first->getFromX() << ", " << move.first->getFromY() << "),";
  std::cout << "  To (" << move.first->getToX() << ", " << move.first->getToY() << "),";
  std::cout << "  Target (" << move.first->getTargetX() << ", " << move.first->getTargetY() << ")" << std::endl;
}

void Log::error(std::string const& message) {
  std::cout << "Error: " << message << std::endl;
}
