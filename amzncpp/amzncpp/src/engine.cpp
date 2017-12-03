#include "engine.h"
#include "log.h"
#include "input.h"

Engine const* const Engine::ENGINE = new Engine();

void Engine::run() const {
  Log::info("Welcome to amzn.cpp! :)");
 
  bool active = true;
  while (active) {
    Board* board = Input::getBoard();
    Player const& userPlayer = Input::getPlayer();
    Player const& currentPlayer = Player::instanceLeft();

    int moves = 0;
    while (board->getScope(currentPlayer)) {
    }
    reportLoser(currentPlayer);
    delete board;
  }
}

void Engine::reportLoser(Player const& loser) const {
  Log::info(loser.getLabel() + " cannot move. " + loser.next().getLabel() + "has won! :D");
}
