#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

namespace game_scene {
class MainMenuScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene *createScene();

  virtual bool init();

  CREATE_FUNC(MainMenuScene);

  void onPlayClicked(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

  void onSolveClicked(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};
}// namespace game_scene