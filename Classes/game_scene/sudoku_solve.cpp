#include "sudoku_solve.h"
#include "cocos2d.h"

using game_scene::SudokuSolve;

USING_NS_CC;

USING_NS_CC_EXT;

Scene* SudokuSolve::createScene() {
  auto scene = Scene::create();

  auto layer = SudokuSolve::create();

  scene->addChild(layer);
  return scene;
}
