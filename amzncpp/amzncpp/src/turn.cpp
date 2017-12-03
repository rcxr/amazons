#include "turn.h"

TurnManager::TurnManager(Player const& player) : current(player.getType()), count(0) {}

Player const& TurnManager::getCurrent() const {
  return Player::instance(current);
}

int TurnManager::getCount() const {
  return count;
}

void TurnManager::nextTurn() {
  current = getCurrent().next().getType();
  ++count;
}

bool TurnManager::isTheirTurn(Player const& player) const {
  return player.getType() == current;
}
