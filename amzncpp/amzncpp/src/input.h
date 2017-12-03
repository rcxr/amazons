#pragma once
#include <unordered_map>
#include "board.h"
#include "calculator.h"
#include "canonical.h"

namespace Input {
  Board* getBoard();
  Player const& getPlayer();
  bool getRetry();
  Move* getMove(Board const* board, Player const& player);
  CalculatorHeuristic getMinMax();
  std::unordered_map<unsigned, Canonical*> getGuruDB(std::string const& filename);
}
