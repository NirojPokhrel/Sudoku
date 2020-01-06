#include "game_util.h"
#include <iostream>

namespace game_util {
game_board GetNewGame() {
#if 0
  game_board brd = {{{5, 3, 0, 0, 7, 0, 0, 0, 0},
                     {6, 0, 0, 1, 9, 5, 0, 0, 0},
                     {0, 9, 8, 0, 0, 0, 0, 6, 0},
                     {8, 0, 0, 0, 6, 0, 0, 0, 3},
                     {4, 0, 0, 8, 0, 3, 0, 0, 1},
                     {7, 0, 0, 0, 2, 0, 0, 0, 6},
                     {0, 6, 0, 0, 0, 0, 2, 8, 0},
                     {0, 0, 0, 4, 1, 9, 0, 0, 5},
                     {0, 0, 0, 0, 8, 0, 0, 7, 9}}};
#else
  game_board brd = {{{0, 0, 0, 0, 0, 0, 6, 8, 0},
                     {0, 0, 0, 0, 7, 3, 0, 0, 9},
                     {3, 0, 9, 0, 0, 0, 0, 4, 5},
                     {4, 9, 0, 0, 0, 0, 0, 0, 0},
                     {8, 0, 3, 0, 5, 0, 9, 0, 2},
                     {0, 0, 0, 0, 0, 0, 0, 3, 6},
                     {9, 6, 0, 0, 0, 0, 3, 0, 8},
                     {7, 0, 0, 6, 8, 0, 0, 0, 0},
                     {0, 2, 8, 0, 0, 0, 0, 0, 0}}};
#endif
  return brd;
}

std::pair<uint8_t, uint8_t> ConvertIndexToPoint(uint8_t index) {
  std::pair<uint8_t, uint8_t> point;
  point.first = index / 9;
  point.second = index % 9;

  return point;
}

uint8_t ConvertPointToIndex(const std::pair<uint8_t, uint8_t> &point) {
  return static_cast<uint8_t>(9 * point.first + point.second);
}

inline bool VerticalOk(const game_board &brd, const cpoint &entry,
                       uint8_t value) {
  for (uint8_t i = 0; i < 9; ++i) {
    if (brd[entry.first][i] == value) {
      return false;
    }
  }
  return true;
}

inline bool HorizontalOk(const game_board &brd, const cpoint &entry,
                         uint8_t value) {
  for (uint8_t i = 0; i < 9; ++i) {
    if (brd[i][entry.second] == value) {
      return false;
    }
  }
  return true;
}

inline bool BoxOk(const game_board &brd, const cpoint &entry, uint8_t value) {
  uint8_t i = static_cast<uint8_t>(entry.first - entry.first % 3);
  uint8_t j = static_cast<uint8_t>(entry.second - entry.second % 3);
  uint8_t i_end = static_cast<uint8_t>(i + 3);
  uint8_t j_end = static_cast<uint8_t>(j + 3);
  for (; i < i_end; ++i) {
    for (; j < j_end; ++j) {
      if (brd[i][j] == value) {
        return false;
      }
    }
  }
  return true;
}

bool IsEntryValid(const game_board &brd, const cpoint &entry, uint8_t value) {
  // check the box i.e. 3x3 board
  // check the vertical and horizontal region for overlapping
  return VerticalOk(brd, entry, value) && HorizontalOk(brd, entry, value) &&
         BoxOk(brd, entry, value);
}

bool IsSpaceFilled(const game_board &brd) {
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      if (!brd[i][j]) {
        return false;
      }
    }
  }
  return true;
}
} // namespace game_util