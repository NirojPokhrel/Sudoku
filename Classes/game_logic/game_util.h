#pragma once

#include <array>
#include <utility>

namespace game_util {
using game_board = std::array<std::array<uint8_t, 9>, 9>;
using cpoint = std::pair<uint8_t, uint8_t>;// cartesian point
/// GetNewGame - Create a new game board
game_board GetNewGame();

/// ConvertIndexToPoint - given a index [0, 80], convert it to pair (x, y)
cpoint ConvertIndexToPoint(uint8_t index);

/// ConvertPointToIndex - give a point (x, y) convert it to index [0, 80]
uint8_t ConvertPointToIndex(const cpoint &point);

/// IsEntryValid - Check if the given value is valid to enter to the given point for the board brd
bool IsEntryValid(const game_board &brd, const cpoint &entry, uint8_t value);

/// IsSpaceFilled - Check if the board is complete
bool IsSpaceFilled(const game_board &brd);

/// GenerateRandomNum1To9 - Generate random number from 1 to 9
uint8_t GenerateRandomNum1To9();

/// GenerateRandomNum1To81 - Generate random number from 0 to 80
uint8_t GenerateRandomNum1To81();

/// PrintBoard - Print the 9x9 sudoku board
void PrintBoard(const game_board &brd);
}// namespace game_util