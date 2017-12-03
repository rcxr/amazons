#include "engine.h"
#include "log.h"
#include "input.h"
#include "move.h"
#include "calculator.h"

Engine const& Engine::instance() {
  static Engine instance;
  return instance;
}

void Engine::run() const {
  bool active = true;
  while (active) {
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

    active = Input::getRetry();
  }
}

Engine::Engine() {
  Log::info("Welcome to amzn.cpp! :)");
}

void Engine::report(Board const* board, TurnManager const* turn) const {
  Log::clear();
  Log::info(board);
  Log::title("Result");
  Log::info("After "
    + std::to_string(turn->getCount())
    + " moves "
    + turn->getCurrent().getLabel()
    + " cannot move and "
    + turn->getCurrent().next().getLabel()
    + " has won! :D");
}
