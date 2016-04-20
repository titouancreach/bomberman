#ifdef DEBUG
# define D(x) x
#else
# define D(x)
#endif

#include <iostream>

#include <SFML/Graphics.hpp>

#include "gameStateEditor.h"
#include "gameStateStart.h"
#include "gameStatePlay.h"
#include "gameState.h"

namespace bomber {

  void GameStateStart::draw(const float dt) {

    game_->window_.setView(view_);

    game_->window_.clear(sf::Color::Black);
    game_->window_.draw(game_->background);
  }

  void GameStateStart::update(const float dt) {

  }

  void GameStateStart::handleInput() {

    sf::Event event;

    while ( game_->window_.pollEvent(event) ) {

      switch ( event.type ) {

        /* close the window */
        case sf::Event::Closed:
        {
          game_->window_.close();
          break;
        }

        /* resizing */
        case sf::Event::Resized:
        {
          view_.setSize( event.size.width, event.size.height );
          game_->background.setPosition( game_->window_.mapPixelToCoords(sf::Vector2i(0, 0)) );
          game_->background.setScale(
            float(event.size.width)  / float(game_->background.getTexture()->getSize().x),
            float(event.size.height) / float(game_->background.getTexture()->getSize().y));
          break;
        }
        /* key pressed */
        case sf::Event::KeyPressed:
        {
          if (event.key.code == sf::Keyboard::Escape) game_->window_.close();
          else if(event.key.code == sf::Keyboard::Space) loadGame();
          else if(event.key.code == sf::Keyboard::A) editGame();
          break;
        }
        /* default behaviour */
        default: break;
      }
    }
  }

  GameStateStart::GameStateStart(Game* game) {
      game_ = game;
      sf::Vector2f pos = sf::Vector2f( game_->window_.getSize() );
      view_.setSize(pos);
      pos *= 0.5f;
      view_.setCenter(pos);
  }

  void GameStateStart::editGame() {
    D( std::cout << "@editGame" << std::endl; )
    game_->pushState( new GameStateEditor(game_) );
  }

  void GameStateStart::loadGame() {
    D( std::cout << "@loadGame" << std::endl; )
    game_->pushState( new GameStatePlay(game_) );
  }
}
