#pragma once
#include <string>
#include "tile.h"

enum PlayerType {
  PLAYER_TYPE_LEFT, PLAYER_TYPE_RIGHT
};

class Player {
public:
  static Player const& instanceLeft();
  static Player const& instanceRight();
  static Player const& instance(PlayerType type);

  Tile getTile() const;
  PlayerType getType() const;
  std::string getLabel() const;

  bool isLeft() const;
  bool isRight() const;

  Player const& next() const;
  bool operator==(Player const&other) const;

  Player(Player const&) = delete;
  void operator=(Player const&) = delete;

private:
  explicit Player(PlayerType type);

  PlayerType const type;
};
