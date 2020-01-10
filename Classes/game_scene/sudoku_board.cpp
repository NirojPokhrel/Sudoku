#include "sudoku_board.h"
#include <iostream>

USING_NS_CC;

USING_NS_CC_EXT;

using game_scene::SudokuBoard;

Scene *SudokuBoard::createScene() {
  auto scene = Scene::create();

  auto layer = SudokuBoard::create();

  scene->addChild(layer);
  return scene;
}

// on "init" you need to initialize your instance
bool SudokuBoard::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  if (is_game_) {
    game_state_ = game_util::GetNewGame();
  }
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  // set background
  ui::ImageView *image_view = ui::ImageView::create(background_res_);
  auto scale_x = visibleSize.width / image_view->getContentSize().width;
  auto scale_y = visibleSize.height / image_view->getContentSize().height;
  image_view->setScale(scale_x, scale_y);
  image_view->setPosition(Vec2(origin.x + visibleSize.width / 2,
    origin.y + visibleSize.height / 2));
  this->addChild(image_view);
  // edit box test
  // starting position 91x91
  // width is 87
  // border width is 4
  // 89 horizontal
  int x_pos = constants::kBkLeftSeperation + constants::kBkCellBorder + constants::kBkCellSize / 2;
  int y_pos = constants::kBkImgHeight - constants::kBkTopSeperation - constants::kBkCellBorder - constants::kBkCellSize / 2;
  auto start_pos = std::pair<uint32_t, uint32_t>{ x_pos, y_pos };
  uint32_t size = 3 * (constants::kBkCellSize + constants::kBkCellBorder);
  Create3x3Matrix({ start_pos.first, start_pos.second });
  return true;
}

void SudokuBoard::Create3x3Matrix(const std::pair<uint32_t, uint32_t> &origin) {
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto x_scale = visibleSize.width / constants::kBkImgWidth;
  auto y_scale = visibleSize.height / constants::kBkImgHeight;
  std::pair<uint32_t, uint32_t> current_pos = { 0, 0 };
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (!game_state_[j][i]) {
        ui::EditBox *editName = ui::EditBox::create(
          Size(constants::kBkCellSize * x_scale,
            constants::kBkCellSize * y_scale),
          ui::Scale9Sprite::create("res/wrong_edit_box.png"));
        current_pos.first = origin.first + i * (constants::kBkCellSize + constants::kBkCellBorder);
        current_pos.second = origin.second - j * (constants::kBkCellSize + constants::kBkCellBorder);
        editName->setPosition(
          Vec2(x_scale * current_pos.first, y_scale * current_pos.second));
        editName->setFontSize(50);
        editName->setFontColor(Color3B::RED);
        editName->setOpacity(0);
        editName->setMaxLength(1);
        editName->setInputMode(ui::EditBox::InputMode::NUMERIC);
        editName->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        editName->setDelegate(this);
        editName->setActionTag(9 * j + i);
        sudoku_boxes_[9 * j + i] = editName;
        this->addChild(editName);
      } else {
        ui::TextField *textBox = ui::TextField::create();
        current_pos.first = origin.first + i * (constants::kBkCellSize + constants::kBkCellBorder);
        current_pos.second = origin.second - j * (constants::kBkCellSize + constants::kBkCellBorder);
        textBox->setPosition(
          Vec2(x_scale * current_pos.first, y_scale * current_pos.second));
        textBox->setFontSize(30);
        textBox->setMaxLength(1);
        textBox->setString(std::to_string(game_state_[j][i]));
        sudoku_boxes_[9 * j + i] = nullptr;
        this->addChild(textBox);
      }
    }
  }
}

void SudokuBoard::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox) {
  editBox->setOpacity(100);
}

void SudokuBoard::editBoxEditingDidEndWithAction(
  cocos2d::ui::EditBox *editBox,
  cocos2d::ui::EditBoxDelegate::EditBoxEndAction action) {}

void SudokuBoard::editBoxTextChanged(cocos2d::ui::EditBox *editBox,
  const std::string &text) {}

void SudokuBoard::editBoxReturn(cocos2d::ui::EditBox *editBox) {
  auto text = editBox->getText();
  std::cout << "Strlen : " << std::strlen(text) << std::endl;
  if (std::strlen(text) < 1) {
    return;
  } else if (std::strlen(text) > 2) {
    // usually 1 will be the element and additional null termination '/0'
    editBox->setOpacity(150);
    editBox->setText("?");
  } else if (!std::isdigit(*editBox->getText())) {
    editBox->setOpacity(150);
  } else {
    auto pos = game_util::ConvertIndexToPoint(editBox->getActionTag());
    game_state_[pos.first][pos.second] = 0;
    uint8_t value = std::stoi(editBox->getText());
    if (!game_util::IsEntryValid(game_state_, pos, value)) {
      editBox->setOpacity(150);
    } else {
      editBox->setOpacity(0);
    }
    game_state_[pos.first][pos.second] = value;
    if (game_util::IsSpaceFilled(game_state_)) {
      // game over
    }
  }
  std::cout << editBox->getActionTag() << std::endl;
}

void SudokuBoard::SetGameState(const game_util::game_board &state) {
  game_state_ = state;
  for (uint8_t i = 0; i < 9; i++) {
    for (uint8_t j = 0; j < 9; j++) {
      if (sudoku_boxes_[i * 9 + j] != nullptr) {
        sudoku_boxes_[i * 9 + j]->setText(std::to_string(game_state_[i][j]).c_str());
      }
    }
  }
}
