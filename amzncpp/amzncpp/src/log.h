#pragma once
#include "board.h"

namespace Log {
  void clear();
  void title(std::string const& title);
  void info(std::string const& message);
  void info(Board const* board);
  void info(std::pair<Move*, Board*> move);
  void error(std::string const& message);
}
