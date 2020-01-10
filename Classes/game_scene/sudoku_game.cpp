#include "sudoku_game.h"
#include "cocos2d.h"

using game_scene::SudokuGame;

USING_NS_CC;

USING_NS_CC_EXT;

Scene *SudokuGame::createScene() {
  auto scene = Scene::create();

  auto layer = SudokuGame::create();

  scene->addChild(layer);
  return scene;
}