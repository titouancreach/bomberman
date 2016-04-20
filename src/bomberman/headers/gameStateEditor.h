#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"
#include "gameState.h"

namespace bomber {

class GameStateEditor : public GameState {

public:

  virtual void draw(const float dt);
  virtual void update(const float dt);
  virtual void handleInput();

  GameStateEditor(Game *);

private:

  float zoom_level_;

  sf::View gameView_;
  sf::View guiView_;

  Map map_;
};

}
