#pragma once
#include "sudoku_board.h"

namespace game_scene {
class SudokuGame : public SudokuBoard
{
public:
  SudokuGame() : SudokuBoard("res/empty_layout.png") {}
  static cocos2d::Scene* createScene();
  CREATE_FUNC(SudokuGame);
};
}// namespace game_scene