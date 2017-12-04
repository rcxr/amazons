#pragma once
#include "player.h"

class Move {
public:
  Move(Player const& player, int fromX, int fromY, int toX, int toY, int targetX, int targetY);
  Player const& getPlayer() const;
  std::pair<int, int> const& getFrom() const;
  std::pair<int, int> const& getTo() const;
  std::pair<int, int> const& getTarget() const;
  int getFromX() const;
  int getFromY() const;
  int getToX() const;
  int getToY() const;
  int getTargetX() const;
  int getTargetY() const;

  std::string toString() const;
  Move* negative() const;
  Move* translate(std::pair<int, int> d) const;

private:
  Player const& player;
  std::pair<int, int> const from;
  std::pair<int, int> const to;
  std::pair<int, int> const target;
};
