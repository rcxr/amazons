#include <sstream>
#include "engine.h"
#include "log.h"
#include "input.h"
#include "move.h"
#include "calculator.h"
#include "guru.h"
#include "config.h"

Engine const& Engine::instance() {
  static Engine instance;
  return instance;
}

void Engine::run() const {
  bool active = true;
  while (active) {
    Log::clear();
    auto board = Input::getBoard();
    auto& user = Input::getPlayer();

    auto turn = new TurnManager(Player::instanceLeft());
    while (board->getScope(turn->getCurrent())) {
      Log::clear();
      Log::info(board);
      Move* move = Calculator::instance().calculateGuruMove(board, turn->getCurrent());
      if (!move) {
        move = turn->isTheirTurn(user)
          ? Input::getMove(board, turn->getCurrent())
          : Calculator::instance().calculateMove(board, turn->getCurrent());
      }
      auto temp = board;
      board = board->apply(move);
      turn->nextTurn();

      delete temp;
      delete move;
    }
    report(board, turn);
    delete board;
    delete turn;

    active = Input::getAnswer("Would you like to play again?");
  }
}

void Engine::train() const {
  bool active = true;
  auto id = 0u;
  while (active) {
    if (!Canonical::isValid(id) || Guru::instance().knows(id)) {
      // Not canonical or already known
      ++id;
      continue;
    }

    Canonical* canonical = nullptr;

    unsigned minusId = Canonical::negative(id);
    if (Guru::instance().knows(minusId)) {
      // Negative exists, reusing result
      canonical = Guru::instance().ask(minusId)->negative();
    }
    else {
      Board board(id);
      if (1u < board.getAllRegions().size() || 0 == board.getPlayableRegions().size() || 3 < board.getPlayableRegions()[0]->getBlanks()) {
        // Not canonical or too large, skip it
        ++id;
        continue;
      }
      if (0 == board.getLeftScope() && 0 == board.getRightScope()) {
        // These are zero games, track them
        canonical = new Canonical(id, nullptr, nullptr);
      }
      else {
        Log::clear();
        Log::info(&board);
        bool manual = false;
        Move* leftMove = Calculator::instance().calculateBestOrAsk(&board, Player::instanceLeft(), &manual);
        Move* rightMove = Calculator::instance().calculateBestOrAsk(&board, Player::instanceRight(), &manual);
        if (!manual || Input::getAnswer("Confirm action")) {
          if (GURU_TRAIN_MANUAL_FLAG || leftMove && rightMove) {
            canonical = new Canonical(id, leftMove, rightMove);
          }
          else {
            ++id;
          }
        }
      }
    }
    if (canonical) {
      // TODO: condition this
      Input::saveCanonical(id);
      // Learn new canonical position
      Guru::instance().learn(canonical);
      // Save what we have learnt
      Guru::instance().persist();
      ++id;
    }
  }
}

Engine::Engine() {
  Log::title("amzn.cpp");
  Log::info("Starting engine...");
  Calculator::instance();
  Guru::instance();
  Log::info("Engine up and running");
}

void Engine::report(Board const* board, TurnManager const* turn) const {
  Log::clear();
  Log::info(board);
  Log::title("Result");
  std::ostringstream s;
  s <<
    "After " <<
    turn->getCount() <<
    " moves " <<
    turn->getCurrent().getLabel() <<
    " cannot move and " <<
    turn->getCurrent().next().getLabel() <<
    " has won! :D";
  Log::info(s.str());
}
