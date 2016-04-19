#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.h"

namespace bomber {

  class GameStatePlay : public GameState {

  public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStatePlay(Game *);

  private:

    sf::View gameView_;
    sf::View guiView_;
  };

}
