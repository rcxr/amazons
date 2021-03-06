#pragma once
#include <map>
#include "canonical.h"

class Guru {
public:
  static Guru& instance();

  bool knows(unsigned id) const;
  Canonical const* ask(unsigned id) const;
  void learn(Canonical const* canonical);
  void persist() const;

  Guru(Guru const&) = delete;
  void operator=(Guru const&) = delete;

private:
  Guru();
  ~Guru();
  std::map<unsigned, Canonical const*> db;
};
