#include "player.h"

Player const* const Player::LEFT = new Player(PLAYER_TYPE_LEFT);
Player const* const Player::RIGHT = new Player(PLAYER_TYPE_RIGHT);

Tile Player::getTile() const {
  return isLeft() ? TILE_LEFT : TILE_RIGHT;
}

bool Player::isLeft() const {
  return PLAYER_TYPE_LEFT == type;
}

bool Player::isRight() const {
  return PLAYER_TYPE_RIGHT == type;
}

Player::Player(PlayerType type) : type(type) {}
