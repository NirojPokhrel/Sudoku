#pragma once

#include "game_util.h"
#include <array>

namespace game_logic {
/// SudokuSolver - solve the sudoku given the problem
class SudokuSolver
{
public:
  /// Constructor
  ///       @param1 (current) : 9X9 sudoku Game Board
  ///       @param2  (sol_count) : number of possible solution given the state
  SudokuSolver(const game_util::game_board &state, bool sol_count = false)
    : game_state_(state), solution_count_(sol_count) {}

  /// Solve - Solve the sudoku if possible
  void Solve();

  /// GetSolutionCount - Number of solution given the game state. Solve should prceed this call.
  ///       @return - number of solution
  uint32_t GetSolutionCount() const { return counter_; }

  /// GetState - Get the solved state. Solve should preceed this call and GetSolutionCount() == 1 for valid sudolu
  ///     @return - solved game_util::game_board
  game_util::game_board GetState() { return game_state_; }

private:
  struct node
  {
    uint8_t selected{ 0 };
    std::array<bool, 9> options{ 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  };
  void CreateConstrained(uint8_t x, uint8_t y);
  void PropagateConstraints(std::array<node, 81> &selection, uint8_t x, uint8_t y, uint8_t value);
  void PrintConstraints(const std::array<node, 81> &selection);
  bool BackTracking(std::array<node, 81> selection);
  bool CheckValidEntry(const std::array<node, 81> &selection, game_util::cpoint, uint8_t value);
  std::pair<uint8_t, uint8_t>
    GetMinimumIndex(const std::array<node, 81> &selection);
  bool ReduceSingleConstrained(std::array<node, 81> &selection);
  game_util::game_board game_state_;
  std::array<node, 81> option_nodes_;
  bool solution_count_;
  uint32_t counter_{ 0 };
};
}// namespace game_logic