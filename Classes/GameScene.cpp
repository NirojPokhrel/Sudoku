#include "GameScene.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

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

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
#if 0
  ui::EditBox *editName = ui::EditBox::create(
      Size(200, 50), ui::Scale9Sprite::create("res/selected_edit_box.png"));
  editName->setPosition(Vec2(visibleSize.width / 2 + origin.x,
                             visibleSize.height / 2 + origin.y));
  editName->setFontSize(15);
  editName->setFontColor(Color3B::RED);
  editName->setPlaceHolder("Name:");
  editName->setPlaceholderFontColor(Color3B::WHITE);
  editName->setMaxLength(8);
  editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

  this->addChild(editName);
#endif
#if 0
  auto start_pos = std::pair<uint32_t, uint32_t>{origin.x + 50, origin.y + 150};
  uint32_t size = 3 * 60 + 4 * 5;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      Create3x3Matrix({start_pos.first + j * size, start_pos.second + i * size},
                      60, 5);
    }
  }

#endif
  ui::ImageView *image_view = ui::ImageView::create("res/game_layout.png");
  auto scale_x = visibleSize.width / image_view->getContentSize().width;
  auto scale_y = visibleSize.height / image_view->getContentSize().height;
  image_view->setScale(scale_x, scale_y);
  image_view->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height / 2));
  this->addChild(image_view);

  return true;
}

void GameScene::Create3x3Matrix(const std::pair<uint32_t, uint32_t> &origin,
                                uint32_t cell_size, uint32_t cell_diff) {
  std::pair<uint32_t, uint32_t> current_pos = {0, 0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ui::EditBox *editName = ui::EditBox::create(
          Size(cell_size, cell_size),
          ui::Scale9Sprite::create("res/selected_edit_box.png"));
      current_pos.first = origin.first + i * (cell_size + cell_diff);
      current_pos.second = origin.second + j * (cell_size + cell_diff);
      editName->setPosition(Vec2(current_pos.first, current_pos.second));
      editName->setFontSize(50);
      editName->setFontColor(Color3B::RED);
      editName->setPlaceholderFontColor(Color3B::WHITE);
      editName->setMaxLength(1);
      editName->setInputMode(ui::EditBox::InputMode::NUMERIC);
      editName->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
      editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

      this->addChild(editName);
    }
  }
}
