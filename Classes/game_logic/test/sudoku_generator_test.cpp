#include "../sudoku_generator.h"
#include <gtest/gtest.h>

TEST(SudokuGenerator, GenerateBoard) {
  game_logic::SudokuGenerator sudoku_gen;
  sudoku_gen.GenerateBoard(40);
  auto CountEmptyElem = [](const game_util::game_board &brd) {
    int counter = 0;
    for (const auto &row : brd) {
      for (auto elem : row) {
        if (elem == 0) {
          counter++;
        }
      }
    }
    return counter;
  };
  auto brd = sudoku_gen.GenerateBoard(40);
  EXPECT_EQ(40, CountEmptyElem(brd));
  brd = sudoku_gen.GenerateBoard(30);
  EXPECT_EQ(30, CountEmptyElem(brd));
  brd = sudoku_gen.GenerateBoard(50);
  EXPECT_EQ(50, CountEmptyElem(brd));
}