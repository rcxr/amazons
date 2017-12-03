#pragma once
#include "turn.h"

class Engine {
public:
  static Engine const* const ENGINE;

  void run() const;
private:
  Engine();

  void report(TurnManager const* turn) const;
};
