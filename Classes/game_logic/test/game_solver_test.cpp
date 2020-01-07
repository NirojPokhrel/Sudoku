#include "../game_solver.h"
#include "../game_util.h"
#include <gtest/gtest.h>

TEST(GameSolver, DISABLED_InitializeBoard) {
  auto game = game_util::GetNewGame();
  game_logic::SudokuSolver solver(game);
  solver.InitNode();
}