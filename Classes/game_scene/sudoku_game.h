#pragma once
#include "sudoku_board.h"

namespace game_scene {
class SudokuGame : public SudokuBoard
{
public:
  SudokuGame() : SudokuBoard("res/empty_layout.png") {}
  static cocos2d::Scene* createScene();
  CREATE_FUNC(SudokuGame);
  virtual bool init();

private:
  void onPlayPauseClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void onSolveClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  bool paused_{ false };
  cocos2d::ui::TextField* timeCouter;
  cocos2d::ui::TextField* statusField;
  cocos2d::ui::Button* playPauseButton;
  float seconds_{ 0 };
  float minutes_{ 0 };
};
}// namespace game_scene