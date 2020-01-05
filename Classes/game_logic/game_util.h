#pragma once

#include <array>
#include <utility>

namespace game_util {
using game_board = std::array<std::array<uint8_t, 9>, 9>;
using cpoint = std::pair<uint8_t, uint8_t>; // cartesian point

game_board GetNewGame();
cpoint ConvertIndexToPoint(uint8_t index);
uint8_t ConvertPointToIndex(const cpoint &point);
bool IsEntryValid(const game_board &brd, const cpoint &entry, uint8_t value);
bool IsSpaceFilled(const game_board &brd);
} // namespace game_util