#include "player.h"

Player const& Player::instanceLeft() {
  static Player instance(PLAYER_TYPE_LEFT);
  return instance;
}

Player const& Player::instanceRight() {
  static Player instance(PLAYER_TYPE_RIGHT);
  return instance;
}

Player const& Player::instance(PlayerType type) {
  switch(type) {
  case PLAYER_TYPE_LEFT: return instanceLeft();
  case PLAYER_TYPE_RIGHT: return instanceRight();
  default: throw;
  }
}

Tile Player::getTile() const {
  return isLeft() ? TILE_LEFT : TILE_RIGHT;
}

PlayerType Player::getType() const {
  return type;
}

std::string Player::getLabel() const {
  return isLeft() ? "left" : "right";
}

bool Player::isLeft() const {
  return PLAYER_TYPE_LEFT == type;
}

bool Player::isRight() const {
  return PLAYER_TYPE_RIGHT == type;
}

Player const& Player::next() const {
  return PLAYER_TYPE_LEFT == type ? instanceRight() : instanceLeft();
}

bool Player::operator==(Player const& other) const {
  return type == other.type;
}

Player::Player(PlayerType type) : type(type) {}
