#pragma once
#include "../definitions.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "sudoku_board.h"
#include "ui/CocosGUI.h"

namespace game_scene {
class SudokuSolve : public SudokuBoard
{
public:
  SudokuSolve() : SudokuBoard("res/solution_page.png", /*is_game*/ false) {}
  static cocos2d::Scene* createScene();

  virtual bool init();
  CREATE_FUNC(SudokuSolve);
  void touchEvent(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};
}// namespace game_scene