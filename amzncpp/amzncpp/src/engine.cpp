#include <sstream>
#include "engine.h"
#include "log.h"
#include "input.h"
#include "move.h"
#include "calculator.h"
#include "guru.h"

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
      Move* move = turn->isTheirTurn(user)
        ? Input::getMove(board, turn->getCurrent())
        : Calculator::instance().calculateMove(board, turn->getCurrent());
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
      ++id;
      continue;
    }
    auto board = new Board(id);
    if (1u < board->getAllRegions().size() || !board->getLeftScope() && !board->getRightScope()) {
      ++id;
      delete board;
      continue;
    }
    Log::clear();
    Log::info(board);
    Move* leftMove = Calculator::instance().calculateBestOrAsk(board, Player::instanceLeft());
    Move* rightMove = Calculator::instance().calculateBestOrAsk(board, Player::instanceRight());
    bool automated = true;
    if (board->getLeftScope() && !leftMove) {
      automated = false;
      leftMove = Input::getMove(board, Player::instanceLeft());
    }
    if (board->getRightScope() && !rightMove) {
      automated = false;
      rightMove = Input::getMove(board, Player::instanceRight());
    }
    if (automated || Input::getAnswer("Confirm action")) {
      Canonical* canonical = new Canonical(id, leftMove, rightMove);
      Guru::instance().learn(canonical);
      Input::saveCanonical(id);
      ++id;
    }
    delete board;
    // Save what we have learnt
    Guru::instance().persist();
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
