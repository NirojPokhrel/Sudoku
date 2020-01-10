#include "sudoku_solve.h"
#include "../game_logic/game_solver.h"
#include <iostream>
using game_scene::SudokuSolve;

USING_NS_CC;

USING_NS_CC_EXT;

Scene* SudokuSolve::createScene() {
  auto scene = Scene::create();

  auto layer = SudokuSolve::create();

  scene->addChild(layer);
  return scene;
}


bool SudokuSolve::init() {
  if (!SudokuBoard::init()) {
    return false;
  }
  auto solveButton =
    ui::Button::create("res/solve.png");
  auto visibleSize = Director::getInstance()->getVisibleSize();
  solveButton->setPosition(Vec2(
    visibleSize.width - 275,
    200));
  this->addChild(solveButton);
  solveButton->addTouchEventListener(
    CC_CALLBACK_2(SudokuSolve::touchEvent, this));

  return true;
}

void SudokuSolve::touchEvent(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::BEGAN: {
    break;
  }
  case cocos2d::ui::Widget::TouchEventType::MOVED: {
    break;
  }
  case cocos2d::ui::Widget::TouchEventType::CANCELED: {
    break;
  }
  case cocos2d::ui::Widget::TouchEventType::ENDED: {
    // solve the problem
    auto current_state = SudokuBoard::GetGameState();
    game_logic::SudokuSolver solver(current_state);
    solver.InitNode();
    auto solved_state = solver.GetState();
    SudokuBoard::SetGameState(solved_state);
    break;
  }
  }
}
