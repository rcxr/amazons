#include "engine.h"
#include "config.h"

int main() {
  if (GURU_TRAIN_FLAG) {
    Engine::instance().train();
  }

  Engine::instance().run();
}
