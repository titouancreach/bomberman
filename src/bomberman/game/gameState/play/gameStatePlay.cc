#include <SFML/Graphics.hpp>

#include "gameState.h"
#include "gameStatePlay.h"

namespace bomber {

  void GameStatePlay::draw(const float dt)
  {
      game_->window_.clear(sf::Color::Black);
      game_->window_.draw(game_->background);

      return;
  }

  void GameStatePlay::update(const float dt)
  {
      return;
  }

  void GameStatePlay::handleInput()
  {
      sf::Event event;

      while(game_->window_.pollEvent(event))
      {
          switch(event.type)
          {
              /* Close the window */
              case sf::Event::Closed:
              {
                  game_->window_.close();
                  break;
              }
              /* Resize the window */
              case sf::Event::Resized:
              {
                  gameView_.setSize(event.size.width, event.size.height);
                  guiView_.setSize(event.size.width, event.size.height);
                  game_->background.setPosition(game_->window_.mapPixelToCoords(sf::Vector2i(0, 0), guiView_));
                  game_->background.setScale(
                      float(event.size.width) / float(game_->background.getTexture()->getSize().x),
                      float(event.size.height) / float(game_->background.getTexture()->getSize().y));
                  break;
              }
              default: break;
          }
      }

      return;
  }

  GameStatePlay::GameStatePlay(Game* game)
  {
      game_ = game;
      sf::Vector2f pos = sf::Vector2f(game_->window_.getSize());
      guiView_.setSize(pos);
      gameView_.setSize(pos);
      pos *= 0.5f;
      guiView_.setCenter(pos);
      gameView_.setCenter(pos);
  }

}
