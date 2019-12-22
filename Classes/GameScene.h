#pragma once

#include "cocos2d.h"
#include <utility>

class GameScene : public cocos2d::Layer {
public:
  static cocos2d::Scene *createScene();

  virtual bool init();

  // implement the "static create()" method manually
  CREATE_FUNC(GameScene);

private:
  void Create3x3Matrix(const std::pair<uint32_t, uint32_t> &origin,
                       uint32_t cell_size, uint32_t cell_diff);
};
