#include "../game_util.h"
#include <gtest/gtest.h>

namespace {
game_util::game_board GetEmptyBoard() {
  game_util::game_board game;
  for (auto &y : game) {
    for (auto &x : y) {
      x = 0;
    }
  }
  return game;
}

game_util::game_board GetRandomlyFilledGame() {
  game_util::game_board game;
  for (auto &y : game) {
    for (auto &x : y) {
      x = 1;
    }
  }
  return game;
}
} // namespace

TEST(GameUtil, GetNewGame) {
  // game should only contain digits from 0-9.
  auto game = game_util::GetNewGame();
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      EXPECT_LE(game[i][j], 9);
    }
  }
}

TEST(GameUtil, ConvertIndexToPoint) {
  auto DeducePoint = [](uint8_t idx, uint8_t x, uint8_t y) {
    auto point = game_util::ConvertIndexToPoint(idx);
    EXPECT_EQ(point.first, x);
    EXPECT_EQ(point.second, y);
  };
  DeducePoint(80, 8, 8);
  DeducePoint(8, 0, 8);
  DeducePoint(0, 0, 0);
  DeducePoint(72, 8, 0);
}

TEST(GameUtil, ConvertPointToIndex) {
  auto DeduceIndex = [](uint8_t x, uint8_t y, uint8_t idx) {
    EXPECT_EQ(idx, game_util::ConvertPointToIndex(std::make_pair(x, y)));
  };
  DeduceIndex(8, 8, 80);
  DeduceIndex(0, 8, 8);
  DeduceIndex(0, 0, 0);
  DeduceIndex(8, 0, 72);
}

TEST(GameUtil, IsEntryValid) {
  auto game = GetEmptyBoard();
  EXPECT_TRUE(game_util::IsEntryValid(game, {0, 0}, 1));

  game[0][0] = 1;
  // horizontal has same value
  EXPECT_FALSE(game_util::IsEntryValid(game, {0, 5}, 1));

  // vertical has same value
  EXPECT_FALSE(game_util::IsEntryValid(game, {5, 0}, 1));

  // same 3x3 box has same value
  EXPECT_FALSE(game_util::IsEntryValid(game, {2, 1}, 1));
}

TEST(GameUtil, IsSpaceFilled) {
  auto game = game_util::GetNewGame();
  EXPECT_FALSE(game_util::IsSpaceFilled(game));

  game = GetRandomlyFilledGame();
  EXPECT_TRUE(game_util::IsSpaceFilled(game));
}