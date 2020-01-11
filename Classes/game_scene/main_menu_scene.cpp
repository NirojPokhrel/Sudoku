#include "main_menu_scene.h"
#include "sudoku_game.h"
#include "sudoku_solve.h"

USING_NS_CC;

USING_NS_CC_EXT;

using game_scene::MainMenuScene;

cocos2d::Scene *MainMenuScene::createScene() {
  auto scene = Scene::create();

  auto layer = MainMenuScene::create();

  scene->addChild(layer);
  return scene;
}

bool MainMenuScene::init() {
  if (!Layer::init()) {
    return false;
  }
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  // set background
  ui::ImageView *image_view = ui::ImageView::create("res/front_page.png");
  auto scale_x = visibleSize.width / image_view->getContentSize().width;
  auto scale_y = visibleSize.height / image_view->getContentSize().height;
  image_view->setScale(scale_x, scale_y);
  image_view->setPosition(Vec2(origin.x + visibleSize.width / 2,
    origin.y + visibleSize.height / 2));
  this->addChild(image_view);

  auto newButton =
    ui::Button::create("res/play.png");
  newButton->setPosition(Vec2(
    visibleSize.width / 2,
    visibleSize.height / 2));
  this->addChild(newButton);
  newButton->addTouchEventListener(
    CC_CALLBACK_2(MainMenuScene::onPlayClicked, this));

  auto solveButton =
    ui::Button::create("res/solve.png");
  solveButton->setPosition(Vec2(
    visibleSize.width / 2,
    visibleSize.height / 2 - 150));
  this->addChild(solveButton);
  solveButton->addTouchEventListener(
    CC_CALLBACK_2(MainMenuScene::onSolveClicked, this));

  return true;
}


void MainMenuScene::onPlayClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::ENDED: {
    auto scene = game_scene::SudokuGame::createScene();
    auto transitionFade = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(scene);
  }
  }
}

void MainMenuScene::onSolveClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::ENDED: {
    auto scene = game_scene::SudokuSolve::createScene();
    auto transitionFade = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(scene);
  }
  }
}