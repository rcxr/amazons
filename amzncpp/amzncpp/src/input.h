#pragma once
#include "board.h"
#include "calculator.h"

namespace Input {
  Board* getBoard();
  Player const& getPlayer();
  bool getRetry();
  Move* getMove(Board const* board, Player const& player);
  CalculatorHeuristic getMinMax();
}
