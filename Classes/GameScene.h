#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "extensions/cocos-ext.h"
#include "game_logic/game_util.h"
#include "ui/CocosGUI.h"
#include <utility>

namespace cocoui = cocos2d::ui;
class GameScene : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate {
public:
  static cocos2d::Scene *createScene();

  virtual bool init();

  // implement the "static create()" method manually
  CREATE_FUNC(GameScene);

  // override from cocos2d::EditBoxDelegate
  void editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox) override;
  void editBoxEditingDidEndWithAction(
      cocos2d::ui::EditBox *editBox,
      cocos2d::ui::EditBoxDelegate::EditBoxEndAction action) override;
  void editBoxTextChanged(cocos2d::ui::EditBox *editBox,
                          const std::string &text) override;
  void editBoxReturn(cocos2d::ui::EditBox *editBox) override;

private:
  void Create3x3Matrix(const std::pair<uint32_t, uint32_t> &origin);

  game_util::game_board game_state_;
};
