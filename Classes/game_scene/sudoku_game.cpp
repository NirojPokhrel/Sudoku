#include "sudoku_game.h"
#include "../game_logic/game_solver.h"
#include "../game_logic/sudoku_generator.h"
#include "cocos2d.h"
#include <iomanip>

using game_scene::SudokuGame;

USING_NS_CC;

USING_NS_CC_EXT;

Scene *SudokuGame::createScene() {
  auto scene = Scene::create();

  auto layer = SudokuGame::create();

  scene->addChild(layer);
  return scene;
}

bool SudokuGame::init() {
  if (!SudokuBoard::init()) {
    return false;
  }
  auto newButton =
    ui::Button::create("res/new.png");
  auto visibleSize = Director::getInstance()->getVisibleSize();
  newButton->setPosition(Vec2(
    visibleSize.width - 275,
    visibleSize.height - 175));
  newButton->addTouchEventListener(
    CC_CALLBACK_2(SudokuGame::onNewClicked, this));
  this->addChild(newButton);

  playPauseButton =
    ui::Button::create("res/pause.png");
  playPauseButton->setPosition(Vec2(
    visibleSize.width - 275,
    newButton->getBottomBoundary() - 100));
  this->addChild(playPauseButton);
  playPauseButton->addTouchEventListener(
    CC_CALLBACK_2(SudokuGame::onPlayPauseClicked, this));

  auto solveButton =
    ui::Button::create("res/solve.png");
  solveButton->setPosition(Vec2(
    visibleSize.width - 275,
    playPauseButton->getBottomBoundary() - 100));
  this->addChild(solveButton);
  solveButton->addTouchEventListener(
    CC_CALLBACK_2(SudokuGame::onSolveClicked, this));

  timeCouter = ui::TextField::create();
  timeCouter->setPosition(
    Vec2(visibleSize.width - 275, solveButton->getBottomBoundary() - 100));
  timeCouter->setFontSize(120);
  timeCouter->setString("00:00");
  this->addChild(timeCouter);

  statusField = ui::TextField::create();
  statusField->setPosition(
    Vec2(145, visibleSize.height - 30));
  statusField->setTextColor(Color4B::RED);
  statusField->setFontSize(30);
  statusField->setString("Playing ...");
  this->addChild(statusField);
  game_scene::SudokuBoard::SetGameOverCallback([&]() {
    paused_ = true;
    statusField->setString("You Won ...");
  });

  Director::getInstance()
    ->getScheduler()
    ->schedule([&](float dt) {
      if (paused_) {
        return;
      }
      seconds_ += dt;
      if (seconds_ > 59) {
        seconds_ -= 60;
        minutes_ += 1;
        if (minutes_ > 59) {
          minutes_ = 0;
        }
      }
      std::stringstream ss;
      ss << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(minutes_) << ":"
         << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(seconds_);
      timeCouter->setString(ss.str());
    },
      this,
      1.0f,
      false,
      "schedulerKey");

  return true;
}

void SudokuGame::onPlayPauseClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::ENDED: {
    if (paused_) {
      paused_ = false;
      playPauseButton->loadTextures("res/pause.png", "res/pause.png");
      statusField->setString("Playing ...");
    } else {
      paused_ = true;
      playPauseButton->loadTextures("res/play.png", "res/play.png");
      statusField->setString("Paused ...");
    }

    break;
  }
  }
}

void SudokuGame::onSolveClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::ENDED: {
    // solve the problem
    auto current_state = SudokuBoard::GetGameState();
    game_logic::SudokuSolver solver(current_state);
    solver.Solve();
    auto solved_state = solver.GetState();
    SudokuBoard::SetGameState(solved_state);
    break;
  }
  }
}

void SudokuGame::onNewClicked(Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::ENDED: {
    auto scene = game_scene::SudokuGame::createScene();
    auto transitionFade = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(scene);
    break;
  }
  }
}
