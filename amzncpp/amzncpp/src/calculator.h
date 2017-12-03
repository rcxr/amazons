#pragma once
#include "move.h"
#include "board.h"

enum CalculatorHeuristic {
  CALCULATOR_HEURISTIC_MINMAX,
  CALCULATOR_HEURISTIC_MAXMIN
};

class Calculator {
public:
  static Calculator& instance();
  Calculator(Calculator const&) = delete;
  void operator=(Calculator const&) = delete;
  Move* calculateMove(Board const* board, Player const& player) const;

private:
  Calculator() {}
  static std::pair<Move*, Board*> calculateMinMaxMove(std::vector<std::pair<Move*, Board*>> const& results, Player const& player);
  static std::pair<Move*, Board*> calculateMaxMinMove(std::vector<std::pair<Move*, Board*>> const& results, Player const& player);
};