#pragma once
#include <unordered_map>
#include "canonical.h"

class Guru {
public:
  static Guru const& instance();

  Guru(Guru const&) = delete;
  void operator=(Guru const&) = delete;

private:
  Guru();
  ~Guru();
  std::unordered_map<unsigned, Canonical*> const db;
};
