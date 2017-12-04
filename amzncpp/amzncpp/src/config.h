#pragma once

#define BOARD_DEFAULT_ROWS 10
#define BOARD_DEFAULT_COLS 10

#define CHAR_BLANK_EVEN ' '
#define CHAR_BLANK_ODD (unsigned char)176
#define CHAR_LEFT_1 (unsigned char)195
#define CHAR_LEFT_2 (unsigned char)180
#define CHAR_RIGHT_1 (unsigned char)204
#define CHAR_RIGHT_2 (unsigned char)185
#define CHAR_VOID (unsigned char)178
#define CHAR_OUT_OF_BOARD (unsigned char)219
#define CHAR_OUT_OF_REACH_EVEN (unsigned char)176
#define CHAR_OUT_OF_REACH_ODD (unsigned char)177

#define CANONICAL_ROWS 4
#define CANONICAL_COLS 4
#define CANONICAL_INVALID_ID UINT_MAX
#define CANONICAL_DIR "input/canonical/"

#define GURU_TRAIN_FLAG false
#define GURU_TRAIN_MANUAL_FLAG false
#define GURU_DB_FILE "resources/guru.db"
