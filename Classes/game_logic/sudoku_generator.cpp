#include "sudoku_generator.h"
#include "game_solver.h"

using game_logic::SudokuGenerator;

//  Fill the first row with nine different numbers.
//  Fill the second row which is a shift of the first line by three
//  slots.Fill the third row which is a shift of the second line by three
//  slots.Fill the fourth row which is a shift of the third by one slot.
game_util::game_board SudokuGenerator::GenerateBoard(uint8_t turnoff_count) {
  game_util::game_board brd;
  brd[0] = GenerateRow();
  brd[1] = Shiftby(brd[0], 3);
  brd[2] = Shiftby(brd[1], 3);

  brd[3] = Shiftby(brd[2], 1);
  brd[4] = Shiftby(brd[3], 3);
  brd[5] = Shiftby(brd[4], 3);

  brd[6] = Shiftby(brd[5], 1);
  brd[7] = Shiftby(brd[6], 3);
  brd[8] = Shiftby(brd[7], 3);

  for (uint8_t i = 0; i < turnoff_count;) {
    if (RandomTurnoff(brd)) {
      i++;
      if (i == turnoff_count) {
        break;
      }
    }
  }
  return brd;
}

bool SudokuGenerator::RandomTurnoff(game_util::game_board &brd) {
  uint8_t idx = game_util::GenerateRandomNum1To81();
  // random number is 0 - 80
  auto point = game_util::ConvertIndexToPoint(idx);
  if (brd[point.first][point.second] == 0) {
    return false;
  }
  auto bkup = brd[point.first][point.second];
  brd[point.first][point.second] = 0;
  game_logic::SudokuSolver solver(brd, true);
  solver.InitNode();
  if (solver.GetSolutionCount() == 1) {
    return true;
  }
  brd[point.first][point.second] = bkup;
  return false;
}

std::array<uint8_t, 9> SudokuGenerator::GenerateRow() {
  std::array<uint8_t, 9> row{};
  uint8_t row_pos = 0;

  std::array<bool, 9> next{ true, true, true, true, true, true, true, true, true };
  for (uint8_t i = 0; i < 9; ++i) {
    uint8_t rand_num = game_util::GenerateRandomNum1To9();
    while (rand_num < 9) {
      if (next[rand_num]) {
        row[row_pos++] = rand_num + 1;
        next[rand_num] = false;
        break;
      }
      rand_num++;
      rand_num %= 9;
    }
  }
  return row;
}

std::array<uint8_t, 9>
  SudokuGenerator::Shiftby(const std::array<uint8_t, 9> &row, uint8_t shift) {
  std::array<uint8_t, 9> shifted_row{};
  for (uint8_t i = 0; i < 9; ++i) {
    uint8_t pos = (i - shift + 9) % 9;
    shifted_row[pos] = row[i];
  }
  return shifted_row;
}
