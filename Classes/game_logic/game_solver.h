#pragma once

#include "game_util.h"
#include <array>

namespace game_logic {
class SudokuSolver {
public:
  SudokuSolver(const game_util::game_board &state) : game_state_(state) {}
  void InitNode();

private:
  struct node {
    uint8_t selected{0};
    std::array<bool, 9> options{1, 1, 1, 1, 1, 1, 1, 1, 1};
  };
  void CreateConstrained(uint8_t x, uint8_t y);
  void PropagateConstraints(std::array<node, 81> &selection, uint8_t x,
                            uint8_t y, uint8_t value);
  void PrintConstraints(const std::array<node, 81> &selection);
  bool BackTracking(std::array<node, 81> selection);
  bool CheckValidEntry(const std::array<node, 81> &selection, game_util::cpoint,
                       uint8_t value);
  std::pair<uint8_t, uint8_t>
  GetMinimumIndex(const std::array<node, 81> &selection);
  bool ReduceSingleConstrained(std::array<node, 81> &selection);
  game_util::game_board game_state_;
  std::array<node, 81> option_nodes_;
};
} // namespace game_logic