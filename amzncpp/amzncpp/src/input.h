#pragma once
#include "board.h"
#include "turn.h"

namespace Input {
  Board* getBoard();
  Player const& getPlayer();
  bool getRetry();
  Move* getMove(Board const* board, TurnManager const* turn);
}
