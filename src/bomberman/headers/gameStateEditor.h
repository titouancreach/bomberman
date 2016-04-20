#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"
#include "gameState.h"

namespace bomber {

enum class ActionState { NONE, PANNING };

class GameStateEditor : public GameState {

public:

  virtual void draw(const float dt);
  virtual void update(const float dt);
  virtual void handleInput();

  GameStateEditor(Game *);

private:

  ActionState action_state_;

  float zoom_level_;

  sf::View game_view_;
  sf::View gui_view_;

  sf::Vector2i panning_anchor_;

  Map map_;

};

}
