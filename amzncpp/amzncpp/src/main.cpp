#include "board.h"
#include "input.h"
#include "log.h"

int main() {
  Log::info("Welcome to amzn.cpp! :)");
  Board* board = Input::getBoard();
  delete board;
}
