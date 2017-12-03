#pragma once
#include "player.h"

class Engine {
public:
  static Engine const* const ENGINE;

  void run() const;
private:
  Engine() {}

  void reportLoser(Player const& player, int moves) const;
};
