#include "game_util.h"
#include "sudoku_generator.h"
#include <iomanip>
#include <iostream>
#include <random>

namespace {
inline uint8_t GenerateRandom(double begin, double end) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(begin, end);

  return static_cast<uint8_t>(dist(mt));
}
}// namespace

namespace game_util {
game_board GetNewGame() {
  game_logic::SudokuGenerator sudoku_gen;
  return sudoku_gen.GenerateBoard(40);
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

inline bool VerticalOk(const game_board &brd, const cpoint &entry, uint8_t value) {
  for (uint8_t i = 0; i < 9; ++i) {
    if (brd[entry.first][i] == value) {
      return false;
    }
  }
  return true;
}

inline bool HorizontalOk(const game_board &brd, const cpoint &entry, uint8_t value) {
  for (uint8_t i = 0; i < 9; ++i) {
    if (brd[i][entry.second] == value) {
      return false;
    }
  }
  return true;
}

inline bool BoxOk(const game_board &brd, const cpoint &entry, uint8_t value) {
  auto i = static_cast<uint8_t>(entry.first - entry.first % 3);
  auto j = static_cast<uint8_t>(entry.second - entry.second % 3);
  auto i_end = static_cast<uint8_t>(i + 3);
  auto j_end = static_cast<uint8_t>(j + 3);
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
  return VerticalOk(brd, entry, value) && HorizontalOk(brd, entry, value) && BoxOk(brd, entry, value);
}

bool IsSpaceFilled(const game_board &brd) {
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      if (brd[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

uint8_t GenerateRandomNum1To9() { return GenerateRandom(0.0, 8.9); }

uint8_t GenerateRandomNum1To81() { return GenerateRandom(0.0, 80.9); }

void PrintBoard(const game_board &brd) {
  for (const auto &row : brd) {
    for (const auto &elem : row) {
      std::cout << std::setw(2) << int(elem) << " ";
    }
    std::cout << std::endl;
  }
}
}// namespace game_util