#include "game_solver.h"
#include "game_util.h"
#include <iomanip>
#include <iostream>

using game_logic::SudokuSolver;

void SudokuSolver::InitNode() {
  // initialize data structure with the selected points
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      if (game_state_[i][j] != 0) {
        option_nodes_[game_util::ConvertPointToIndex({ i, j })].selected =
          game_state_[i][j];
      } else {
        CreateConstrained(i, j);
      }
    }
  }

  ReduceSingleConstrained(option_nodes_);

  BackTracking(option_nodes_);
}

bool SudokuSolver::ReduceSingleConstrained(std::array<node, 81> &selection) {
  bool continue_flag = false;
  do {
    continue_flag = false;
    auto idx = GetMinimumIndex(selection);
    if (idx.second == 1) {
      auto point = game_util::ConvertIndexToPoint(idx.first);
      uint8_t value{ 10 };
      for (uint8_t k = 0; k < 9; ++k) {
        if (selection[idx.first].options[k]) {
          value = k + 1;
          break;
        }
      }
      if (value == 10 || !CheckValidEntry(selection, point, value)) {
        // something went wrong
        return false;
      }
      selection[idx.first].selected = value;
      PropagateConstraints(selection, point.first, point.second, value);

      continue_flag = true;
    }
  } while (continue_flag);
  return true;
}

bool SudokuSolver::BackTracking(std::array<node, 81> selection) {
  // make a copy of the state of selection
  // select the least possible selection point
  // continue with constraint propagation
  auto idx = GetMinimumIndex(selection);
  if (idx.first == 100) {
    if (solution_count_) {
      counter_++;
      return false;
    } else {
      for (uint8_t i = 0; i < 9; ++i) {
        for (uint8_t j = 0; j < 9; ++j) {
          game_state_[i][j] = selection[i * 9 + j].selected;
        }
      }
      return true;
    }
  }
  for (uint8_t i = 0; i < 9; ++i) {
    auto selection_copy = selection;
    // make a copy
    if (selection_copy[idx.first].options[i]) {
      selection_copy[idx.first].options[i] = false;
      selection_copy[idx.first].selected = i + 1;
      auto point = game_util::ConvertIndexToPoint(idx.first);
      PropagateConstraints(selection_copy, point.first, point.second, i + 1);
      // PrintConstraints(selection_copy);
      if (!ReduceSingleConstrained(selection_copy)) {
        continue;
      }
      if (BackTracking(selection_copy)) {
        return true;
      }
    }
    // with the changes try to propagate constraints
    // restore
  }
  return false;
}

std::pair<uint8_t, uint8_t>
  SudokuSolver::GetMinimumIndex(const std::array<node, 81> &selection) {
  uint8_t min_count = 9;
  uint8_t min_idx = 100;
  for (uint8_t i = 0; i < 81; ++i) {
    if (selection[i].selected != 0) {
      continue;
    }
    uint8_t count = 0;
    for (uint8_t j = 0; j < 9; ++j) {
      if (selection[i].options[j]) {
        count++;
      }
    }
    if (count < min_count) {
      min_idx = i;
      min_count = count;
    }
  }
  return { min_idx, min_count };
}

void SudokuSolver::PrintConstraints(const std::array<node, 81> &selection) {
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      uint8_t idx = game_util::ConvertPointToIndex({ i, j });
      if (selection[idx].selected == 0) {
        std::cout << int(idx) << " : ";
        for (uint8_t k = 0; k < 9; ++k) {
          if (selection[idx].options[k]) {
            std::cout << int(k + 1) << " ";
          }
        }
        std::cout << std::endl;
      }
    }
  }
}

void SudokuSolver::PropagateConstraints(std::array<node, 81> &selection,
  uint8_t x,
  uint8_t y,
  uint8_t value) {
  // create vertical constrained
  for (uint8_t i = 0; i < 9; ++i) {
    uint8_t idx = game_util::ConvertPointToIndex({ i, y });
    if (selection[idx].selected == 0) {
      selection[idx].options[value - 1] = false;
    }
  }
  // create horizontal constrained
  for (uint8_t i = 0; i < 9; ++i) {
    uint8_t idx = game_util::ConvertPointToIndex({ x, i });
    if (selection[idx].selected == 0) {
      selection[idx].options[value - 1] = false;
    }
  }
  // create square constrained
  auto i = static_cast<uint8_t>(x - x % 3);
  auto j_start = static_cast<uint8_t>(y - y % 3);
  auto i_end = static_cast<uint8_t>(i + 3);
  auto j_end = static_cast<uint8_t>(j_start + 3);
  for (; i < i_end; ++i) {
    for (uint8_t j = j_start; j < j_end; ++j) {
      uint8_t idx = game_util::ConvertPointToIndex({ i, j });
      if (selection[idx].selected == 0) {
        selection[idx].options[value - 1] = false;
      }
    }
  }
}

bool SudokuSolver::CheckValidEntry(const std::array<node, 81> &selection,
  game_util::cpoint point,
  uint8_t value) {
  game_util::game_board brd;
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      uint8_t idx = game_util::ConvertPointToIndex({ i, j });
      brd[i][j] = selection[idx].selected;
    }
  }
  return game_util::IsEntryValid(brd, point, value);
}

void SudokuSolver::CreateConstrained(uint8_t x, uint8_t y) {
  uint8_t idx = game_util::ConvertPointToIndex({ x, y });
  // create horizontal constrained
  for (uint8_t i = 0; i < 9; ++i) {
    if (game_state_[i][y] != 0) {
      option_nodes_[idx].options[game_state_[i][y] - 1] = false;
    }
  }
  // create vertical constrained
  for (uint8_t i = 0; i < 9; ++i) {
    if (game_state_[x][i] != 0) {
      option_nodes_[idx].options[game_state_[x][i] - 1] = false;
    }
  }
  // create square constrained
  auto i = static_cast<uint8_t>(x - x % 3);
  auto j_start = static_cast<uint8_t>(y - y % 3);
  auto i_end = static_cast<uint8_t>(i + 3);
  auto j_end = static_cast<uint8_t>(j_start + 3);
  for (; i < i_end; ++i) {
    for (uint8_t j = j_start; j < j_end; ++j) {
      if (game_state_[i][j] != 0) {
        option_nodes_[idx].options[game_state_[i][j] - 1] = false;
      }
    }
  }
}
