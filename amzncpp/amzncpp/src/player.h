#pragma once
#include "tile.h"

class Player {
public:
  static Player const* const LEFT;
  static Player const* const RIGHT;

  Tile getTile() const;

  bool isLeft() const;
  bool isRight() const;

private:
  enum PlayerType {
    PLAYER_TYPE_LEFT, PLAYER_TYPE_RIGHT
  };

  explicit Player(PlayerType type);

  PlayerType const type;
};
