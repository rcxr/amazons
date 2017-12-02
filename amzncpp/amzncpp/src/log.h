#pragma once
#include <string>
#include "board.h"

namespace Log {
  void error(std::string const& message);
  void info(std::string const& message);
  void info(Board const* board);
}
