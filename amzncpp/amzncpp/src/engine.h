#pragma once
#include "board.h"
#include "turn.h"

class Engine {
public:
  static Engine const& instance();
  void run() const;
  void train() const;
  Engine(Engine const&) = delete;
  void operator=(Engine const&) = delete;
private:
  Engine();
  ~Engine() {}
  void report(Board const* board, TurnManager const* turn) const;
};
