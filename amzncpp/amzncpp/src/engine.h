#pragma once
#include "turn.h"
#include "move.h"

class Board;

class Engine {
public:
  static Engine const* const ENGINE;

  void run() const;
private:
  Engine();

  void report(TurnManager const* turn) const;
};
