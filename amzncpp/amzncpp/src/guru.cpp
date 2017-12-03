#include "guru.h"
#include "input.h"
#include "config.h"
#include "log.h"

Guru const& Guru::instance() {
  static Guru guru;
  return guru;
}

Guru::Guru() : db(Input::getGuruDB(GURU_DB_FILE)) {
  Log::info("Guru up and running (" + std::to_string(db.size()) + " precalculated positions)");
}

Guru::~Guru() {
  for (auto pair : db) {
    delete pair.second;
  }
}
