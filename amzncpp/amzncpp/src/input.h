#pragma once
#include <map>
#include "board.h"
#include "calculator.h"
#include "canonical.h"

namespace Input {
  Board* getBoard();
  Player const& getPlayer();
  bool getAnswer(std::string const& message);
  Move* getMove(Board const* board, Player const& player);
  CalculatorHeuristic getMinMax();
  std::map<unsigned, Canonical const*> getGuruDB(std::string const& filename);

  void saveGuruDB(std::string const& filename, std::map<unsigned, Canonical const*> db);
  void saveCanonical(unsigned id);
}
