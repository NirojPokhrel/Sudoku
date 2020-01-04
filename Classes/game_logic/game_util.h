#pragma once

#include <array>

namespace game_util {
using game_board = std::array<std::array<uint8_t, 9>, 9>;
game_board GetNewGame();
} // namespace game_util