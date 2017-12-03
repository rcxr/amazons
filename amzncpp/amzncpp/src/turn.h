#pragma once
#include "player.h"

class TurnManager {
public:
  explicit TurnManager(Player const& player);
  Player const& getCurrent() const;
  int getCount() const;
  void nextTurn();
  bool isTheirTurn(Player const& player) const;
private:
  PlayerType current;
  int count;
};
