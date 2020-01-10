#pragma once

#include "../game_logic/game_util.h"
#include "cocos2d.h"
#include "definitions.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <utility>

namespace cocoui = cocos2d::ui;
namespace game_scene {
class SudokuBoard : public cocos2d::Layer
  , public cocos2d::ui::EditBoxDelegate
{
public:
  explicit SudokuBoard(std::string res_name, bool is_game = true)
    : background_res_(std::move(res_name)), is_game_(is_game) {}
  static cocos2d::Scene *createScene();

  virtual bool init();

  // override from cocos2d::EditBoxDelegate
  void editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox) override;
  void editBoxEditingDidEndWithAction(
    cocos2d::ui::EditBox *editBox,
    cocos2d::ui::EditBoxDelegate::EditBoxEndAction action) override;
  void editBoxTextChanged(cocos2d::ui::EditBox *editBox,
    const std::string &text) override;
  void editBoxReturn(cocos2d::ui::EditBox *editBox) override;

protected:
  game_util::game_board GetGameState() { return game_state_; }
  void SetGameState(const game_util::game_board &state);

private:
  void Create3x3Matrix(const std::pair<uint32_t, uint32_t> &origin);

  game_util::game_board game_state_{};
  std::array<cocos2d::ui::EditBox *, 81> sudoku_boxes_;

  std::string background_res_;

  bool is_game_;
};
}// namespace game_scene
