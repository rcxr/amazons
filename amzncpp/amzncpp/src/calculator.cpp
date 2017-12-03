#include "calculator.h"
#include "input.h"
#include "log.h"

Calculator& Calculator::instance() {
  static Calculator instance;
  return instance;
}

Move* Calculator::calculateMove(Board const* board, Player const& player) const {
  Log::info("Calculating moves...");
  auto moves = board->getMoves(player);
  Log::info("Found " + std::to_string(moves.size()) + " moves");
  std::vector<std::pair<Move*, Board*>> results;
  Log::info("Calculating resulting boards...");
  for (auto move : moves) {
    results.push_back(std::make_pair(move, board->apply(move)));
  }
  auto maxMin = calculateMaxMinMove(results, player);
  auto minMax = calculateMinMaxMove(results, player);
  Log::title("minmax");
  Log::info(minMax);
  Log::title("maxmin");
  Log::info(maxMin);
  auto chosen = CALCULATOR_HEURISTIC_MAXMIN == Input::getMinMax() ? maxMin.first : minMax.first;
  for (auto result : results) {
    if (result.first != chosen) {
      delete result.first;
    }
    delete result.second;
  }
  return chosen;
}

std::pair<Move*, Board*> Calculator::calculateMinMaxMove(std::vector<std::pair<Move*, Board*>> const& results, Player const& player) {
  auto best = -1;
  auto max = INT_MIN;
  auto min = INT_MAX;
  for (auto i = 0; i < results.size(); ++i) {
    auto board = results[i].second;
    if (board->getScope(player.next()) < min || board->getScope(player.next()) == min && max < board->getScope(player)) {
      max = board->getScope(player);
      min = board->getScope(player.next());
      best = i;
    }
  }
  return results[best];
}

std::pair<Move*, Board*> Calculator::calculateMaxMinMove(std::vector<std::pair<Move*, Board*>> const& results, Player const& player) {
  auto best = -1;
  auto max = INT_MIN;
  auto min = INT_MAX;
  for (auto i = 0; i < results.size(); ++i) {
    auto board = results[i].second;
    if (max < board->getScope(player) || max == board->getScope(player) && board->getScope(player.next()) < min) {
      max = board->getScope(player);
      min = board->getScope(player.next());
      best = i;
    }
  }
  return results[best];
}
