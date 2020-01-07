#include "../sudoku_generator.h"
#include <gtest/gtest.h>

TEST(SudokuGenerator, GenerateBoard) {
  game_logic::SudokuGenerator sudoku_gen;
  sudoku_gen.GenerateBoard(40);
}