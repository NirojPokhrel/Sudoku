#include "GameScene.h"
#include <iostream>

USING_NS_CC;

USING_NS_CC_EXT;

Scene *GameScene::createScene() {
  auto scene = Scene::create();

  auto layer = GameScene::create();

  scene->addChild(layer);
  return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  game_state_ = game_util::GetNewGame();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  // set background
  ui::ImageView *image_view = ui::ImageView::create("res/game_layout.png");
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
  int x_pos = constants::kBkLeftSeperation + constants::kBkCellBorder +
              constants::kBkCellSize / 2;
  int y_pos = constants::kBkImgHeight - constants::kBkTopSeperation -
              constants::kBkCellBorder - constants::kBkCellSize / 2;
  auto start_pos = std::pair<uint32_t, uint32_t>{x_pos, y_pos};
  uint32_t size = 3 * (constants::kBkCellSize + constants::kBkCellBorder);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      Create3x3Matrix({start_pos.first + j * size, start_pos.second - i * size},
                      i, j);
    }
  }
  return true;
}

void GameScene::Create3x3Matrix(const std::pair<uint32_t, uint32_t> &origin,
                                uint32_t box_i, uint32_t box_j) {
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto x_scale = visibleSize.width / constants::kBkImgWidth;
  auto y_scale = visibleSize.height / constants::kBkImgHeight;
  std::pair<uint32_t, uint32_t> current_pos = {0, 0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ui::EditBox *editName = ui::EditBox::create(
          Size(constants::kBkCellSize * x_scale,
               constants::kBkCellSize * y_scale),
          ui::Scale9Sprite::create("res/wrong_edit_box.png"));
      current_pos.first = origin.first + i * (constants::kBkCellSize +
                                              constants::kBkCellBorder);
      current_pos.second = origin.second - j * (constants::kBkCellSize +
                                                constants::kBkCellBorder);
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
      editName->setActionTag(9 * (j + 3 * box_i) + (3 * box_j) + i + 1);

      this->addChild(editName);
    }
  }
}

void GameScene::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox) {
  editBox->setOpacity(100);
}

void GameScene::editBoxEditingDidEndWithAction(
    cocos2d::ui::EditBox *editBox,
    cocos2d::ui::EditBoxDelegate::EditBoxEndAction action) {}

void GameScene::editBoxTextChanged(cocos2d::ui::EditBox *editBox,
                                   const std::string &text) {}

void GameScene::editBoxReturn(cocos2d::ui::EditBox *editBox) {
  auto text = editBox->getText();
  if (std::strlen(text) > 2) {
    // usually 1 will be the element and additional null termination '/0'
    editBox->setOpacity(100);
    editBox->setText("?");
  } else if (editBox->getMaxLength() == 1 &&
             std::isalpha(*editBox->getText())) {
    editBox->setOpacity(100);
  } else {
    editBox->setOpacity(0);
  }
  std::cout << editBox->getActionTag() << std::endl;
}
