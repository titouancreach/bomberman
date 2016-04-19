#pragma once

#include "game.h"

namespace bomber {

  class GameState
  {
  public:

    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;

    virtual ~GameState() {}

  protected:
    Game * game_;

  };

}
