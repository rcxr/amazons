#include <iostream>
#include <fstream>
#include <sstream>
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

int tileToInt(Tile tile) {
  switch (tile) {
  case TILE_BLANK: return 0;
  case TILE_LEFT: return 1;
  case TILE_RIGHT: return 2;
  default: return 3;
  }
}

Board* parseBoardFile(std::string const& filename) {
  std::ifstream stream(filename);
  if (!stream.is_open()) {
    Log::error("File could not be opened");
    return nullptr;
  }

  int rows;
  int cols;
  int tile;
  stream >> tile;
  if (tile < 1) {
    stream >> rows >> cols;
    // We consumed metadata, we need to consume first actual value to be consistent
    stream >> tile;
  }
  else {
    // Value is an actual value, dimensions are as default
    rows = BOARD_DEFAULT_ROWS;
    cols = BOARD_DEFAULT_COLS;
  }

  // Creating dynamic array and setting first position that we already got
  std::vector<Tile> tiles;
  tiles.push_back(intToTile(tile));

  for (auto i = 1; i < rows * cols; ++i) {
    stream >> tile;
    tiles.push_back(intToTile(tile));
  }
  stream.close();

  Log::info("Board successfully loaded from file");
  return new Board(tiles, rows, cols);
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
    board = parseBoardFile(getFile());
  }
  return board;
}

Player const& Input::getPlayer() {
  while (true) {
    Log::info("Choose player (\"left\" or \"l\" for left, \"right\" or \"r\" for right)");
    std::string player;
    getline(std::cin >> std::ws, player);
    if (0 == player.compare("left") || 0 == player.compare("l")) {
      return Player::instanceLeft();
    }
    if (0 == player.compare("right") || 0 == player.compare("r")) {
      return Player::instanceRight();
    }
  }
}

bool Input::getAnswer(std::string const& message) {
  while (true) {
    Log::info(message + " (\"yes\" or \"y\" for yes, \"no\" or \"n\" for no)");
    std::string in;
    getline(std::cin >> std::ws, in);
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
  std::string line;
  getline(std::cin >> std::ws, line);
  int fromX, fromY, toX, toY, targetX, targetY;
  std::stringstream s(line);
  s >> fromX >> fromY >> toX >> toY >> targetX >> targetY;
  return new Move(player, fromX, fromY, toX, toY, targetX, targetY);
}

Move* Input::getMove(Board const* board, Player const& player) {
  Move* move = getMove(player);
  while (!board->isLegalMove(move)) {
    Log::error("That is not a valid move");
    delete move;
    move = getMove(player);
  }
  return move;
}

CalculatorHeuristic Input::getMinMax() {
  while (true) {
    Log::info("Choose heuristic (\"minmax\" or \"min\" for mixman, \"maxmin\" or \"max\" for maxmin)");
    std::string h;
    getline(std::cin >> std::ws, h);
    if (0 == h.compare("min") || 0 == h.compare("minmax")) {
      return CALCULATOR_HEURISTIC_MINMAX;
    }
    if (0 == h.compare("max") || 0 == h.compare("maxmin")) {
      return CALCULATOR_HEURISTIC_MAXMIN;
    }
  }
}

unsigned Input::getGuruHelp(std::set<unsigned> const& canonicalIds) {
  Log::info("Hey, your favorite guru here... I can play optimally in " + std::to_string(canonicalIds.size()) + " subgames");
  if (!getAnswer("Would you like me to play?")) {
    return CANONICAL_INVALID_ID;
  }
  for (auto canonicalId : canonicalIds) {
    Log::info(canonicalId);
    if (getAnswer("What about playing here?")) {
      return canonicalId;
    }
  }
  Log::info("Sorry, that is all I know for now. I will keep training hard!");
  return CANONICAL_INVALID_ID;
}

std::map<unsigned, Canonical const*> Input::getGuruDB(std::string const& filename) {
  std::map<unsigned, Canonical const*> db;
  std::ifstream stream(filename);
  if (!stream.is_open()) {
    Log::error("Guru file could not be opened. Running without guru :(");
    return db;
  }
  unsigned id, fromX, fromY, toX, toY, targetX, targetY;
  bool leftCanMove, rightCanMove;
  while (stream >> id) {
    stream >> leftCanMove >> rightCanMove;
    Move* leftMove = nullptr;
    if (leftCanMove) {
      stream >> fromX >> fromY >> toX >> toY >> targetX >> targetY;
      leftMove = new Move(Player::instanceLeft(), fromX, fromY, toX, toY, targetX, targetY);
    }
    Move* rightMove = nullptr;
    if (rightCanMove) {
      stream >> fromX >> fromY >> toX >> toY >> targetX >> targetY;
      rightMove = new Move(Player::instanceRight(), fromX, fromY, toX, toY, targetX, targetY);
    }
    db[id] = new Canonical(id, leftMove, rightMove);
  }
  stream.close();
  Log::info("Guru database successfully loaded from file");
  return db;
}

void Input::saveGuruDB(std::string const& filename, std::map<unsigned, Canonical const*> db) {
  std::ofstream stream(filename);
  if (!stream.is_open()) {
    Log::error("Guru file could not be opened. Database will not be saved :(");
    return;
  }
  for (auto entry : db) {
    stream << entry.second->toString() << std::endl;
  }
  stream.close();
  Log::info("Guru database successfully saved to file");
}

void Input::saveCanonical(unsigned id) {
  std::ostringstream s;
  s << CANONICAL_DIR << "position" << id << ".txt";
  std::ofstream stream(s.str());
  if (!stream.is_open()) {
    Log::error("File could not be opened. Canonical position will not be saved :(");
    return;
  }
  Board board(id);
  stream << -1 << ' ' << board.getRows() << ' ' << board.getCols() << std::endl;
  for (auto x = 0; x < board.getRows(); ++x) {
    for (auto y = 0; y < board.getCols(); ++y) {
      stream << tileToInt(board.get(x, y)) << ' ';
    }
    stream << std::endl;
  }
  stream.close();
  Log::info("Canonical position successfully saved to file");
}
