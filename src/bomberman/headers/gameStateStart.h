#pragma once

#include <SFML/Graphics.hpp>

#include "gameState.h"

namespace bomber {

  class GameStateStart : public GameState {

  public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStateStart(Game* game);

  private:

    sf::View view_;

    void loadGame();
    void editGame();

  };

}
