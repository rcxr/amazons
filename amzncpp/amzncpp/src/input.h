#pragma once
#include "board.h"

namespace Input {
  Board* getBoard();
  Player const& getPlayer();
  bool getRetry();
  Move* getMove(Player const& player);
}
