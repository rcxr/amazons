#include <set>
#include "calculator.h"
#include "input.h"
#include "log.h"
#include "guru.h"
#include "config.h"

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
  Log::info("minmax", minMax);
  Log::info("maxmin", maxMin);
  auto chosen = CALCULATOR_HEURISTIC_MAXMIN == Input::getMinMax() ? maxMin.first : minMax.first;
  for (auto result : results) {
    if (result.first != chosen) {
      delete result.first;
    }
    delete result.second;
  }
  return chosen;
}

Move* Calculator::calculateBestOrAsk(Board const* board, Player const& player, bool* asked) const {
  auto moves = board->getMoves(player);
  if (1 == moves.size()) {
    return moves[0];
  }
  if (0 == moves.size()) {
    return nullptr;
  }
  for (auto move : moves) {
    delete move;
  }
  if (GURU_TRAIN_MANUAL_FLAG) {
    *asked = true;
    return Input::getMove(board, player);
  }
  return nullptr;
}

Move* Calculator::calculateGuruMove(Board const* board, Player const& player) const {
  std::set<unsigned> canonicalIds;
  for (auto region : board->getPlayableRegions()) {
    auto canonicalId = region->getCanonicalId();
    if (Guru::instance().knows(canonicalId)) {
      canonicalIds.insert(canonicalId);
    }
  }
  if (canonicalIds.empty()) {
    return nullptr;
  }
  unsigned canonicalId = Input::getGuruHelp(canonicalIds);
  if (CANONICAL_INVALID_ID == canonicalId) {
    return nullptr;
  }
  for (auto region : board->getPlayableRegions()) {
    if (canonicalId == region->getCanonicalId()) {
      auto temp = Guru::instance().ask(canonicalId)->getMove(player);
      if (!temp) {
        Log::info("Sorry, that was an optimal move for the other player, let's fallback to normal input!");
      }
      return temp ? temp->translate(region->getCanonicalDelta()) : nullptr;
    }
  }
  throw;
}

Calculator::Calculator() {
  Log::info("MinMax/MaxMin calculator up and running");
}

std::pair<Move*, Board*> Calculator::calculateMinMaxMove(std::vector<std::pair<Move*, Board*>> const& results, Player const& player) {
  auto best = UINT_MAX;
  auto max = INT_MIN;
  auto min = INT_MAX;
  for (auto i = 0u; i < results.size(); ++i) {
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
  auto best = UINT_MAX;
  auto max = INT_MIN;
  auto min = INT_MAX;
  for (auto i = 0u; i < results.size(); ++i) {
    auto board = results[i].second;
    if (max < board->getScope(player) || max == board->getScope(player) && board->getScope(player.next()) < min) {
      max = board->getScope(player);
      min = board->getScope(player.next());
      best = i;
    }
  }
  return results[best];
}
