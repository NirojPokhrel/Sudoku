#pragma once

#include "game_util.h"
#include <array>

namespace game_logic {
// sudoku generated using
// https://gamedev.stackexchange.com/questions/56149/how-can-i-generate-sudoku-puzzles
class SudokuGenerator
{
public:
  /// GenerateBoard - generate a sudoku board with the number of turnoff_count elements turned off
  game_util::game_board GenerateBoard(uint8_t turnoff_count);

private:
  std::array<uint8_t, 9> GenerateRow();
  std::array<uint8_t, 9> Shiftby(const std::array<uint8_t, 9> &row,
    uint8_t shift);
  bool RandomTurnoff(game_util::game_board &brd);
};
}// namespace game_logic