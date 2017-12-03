#include "engine.h"
#include "log.h"
#include "input.h"
#include "move.h"

Engine const* const Engine::ENGINE = new Engine();

void Engine::run() const {
  bool active = true;
  while (active) {
    auto board = Input::getBoard();
    auto& user = Input::getPlayer();

    auto turn = new TurnManager(Player::instanceLeft());
    while (board->getScope(turn->getCurrent())) {
      Move* move = nullptr;
      if (turn->isTheirTurn(user)) {
        move = Input::getMove(turn->getCurrent());
      } else {
        move = Input::getMove(turn->getCurrent());
      }
      if (board->isLegalMove(turn->getCurrent(), move)) {
        // Perform move
        turn->nextTurn();
      }
      delete move;
    }
    report(turn);

    delete board;
    delete turn;

    active = Input::getRetry();
  }
}

Engine::Engine() {
  Log::info("Welcome to amzn.cpp! :)");
}

void Engine::report(TurnManager const* turn) const {
  Log::info("After "
    + std::to_string(turn->getCount())
    + " moves, "
    + turn->getCurrent().getLabel()
    + " cannot move. "
    + turn->getCurrent().next().getLabel()
    + " has won! :D");
}
