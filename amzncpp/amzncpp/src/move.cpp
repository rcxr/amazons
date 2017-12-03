#include "move.h"
Move::Move(Player const& player, int fromX, int fromY, int toX, int toY, int targetX, int targetY) :
  player(player),
  from(std::make_pair(fromX, fromY)),
  to(std::make_pair(toX, toY)),
  target(std::make_pair(targetX, targetY)) {}

Player const& Move::getPlayer() const { return player; }
std::pair<int, int> const& Move::getFrom() const { return from; }
std::pair<int, int> const& Move::getTo() const { return to; }
std::pair<int, int> const& Move::getTarget() const { return target; }
int Move::getFromX() const { return from.first; }
int Move::getFromY() const { return from.second; }
int Move::getToX() const { return to.first; }
int Move::getToY() const { return to.second; }
int Move::getTargetX() const { return target.first; }
int Move::getTargetY() const { return target.second; }