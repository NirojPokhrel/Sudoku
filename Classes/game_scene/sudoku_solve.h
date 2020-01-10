#pragma once
#include "sudoku_board.h"

namespace game_scene {
class SudokuSolve : public SudokuBoard
{
public:
  SudokuSolve() : SudokuBoard("res/solution_page.png", /*is_game*/ false) {}
  static cocos2d::Scene* createScene();
  CREATE_FUNC(SudokuSolve);
};
}// namespace game_scene