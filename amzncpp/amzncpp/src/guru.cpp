#include "guru.h"
#include "input.h"
#include "config.h"
#include "log.h"

Guru& Guru::instance() {
  static Guru guru;
  return guru;
}

bool Guru::knows(unsigned id) const {
  return db.end() != db.find(id);
}

Canonical const* Guru::ask(unsigned id) const {
  if (!knows(id)) { return nullptr; }
  return db.find(id)->second;
}

void Guru::learn(Canonical const* canonical) {
  auto oldValue = ask(canonical->id);
  if (oldValue && oldValue != canonical) {
    delete oldValue;
  }
  db[canonical->id] = canonical;
}

void Guru::persist() const {
  Input::saveGuruDB(GURU_DB_FILE, db);
}

Guru::Guru() : db(Input::getGuruDB(GURU_DB_FILE)) {
  Log::info("Guru up and running (" + std::to_string(db.size()) + " precalculated positions)");
}

Guru::~Guru() {
  for (auto entry : db) {
    delete entry.second;
  }
}
