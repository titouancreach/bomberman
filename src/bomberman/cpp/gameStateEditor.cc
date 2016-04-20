#include <SFML/Graphics.hpp>

#include "gameState.h"
#include "gameStateEditor.h"

namespace bomber {

void GameStateEditor::draw(const float dt)
  {
      game_->window_.clear(sf::Color::Black);

      game_->window_.setView(gui_view_);
      game_->window_.draw(game_->background);

      game_->window_.setView(game_view_);
      map_.draw(game_->window_, dt);

      return;
  }

  void GameStateEditor::update(const float dt)
  {
      return;
  }

  void GameStateEditor::handleInput()
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
                  game_view_.setSize(event.size.width, event.size.height);
                  gui_view_.setSize(event.size.width, event.size.height);
                  game_view_.zoom(zoom_level_);
                  game_->background.setPosition(game_->window_.mapPixelToCoords(sf::Vector2i(0, 0), gui_view_));
                  game_->background.setScale(
                      float(event.size.width) / float(game_->background.getTexture()->getSize().x),
                      float(event.size.height) / float(game_->background.getTexture()->getSize().y));
                  break;
              }

              case sf::Event::MouseMoved: {
                  /* Pan the camera */
                  if( this->action_state_ == ActionState::PANNING ) {
                      sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(game_->window_) - this->panning_anchor_);
                      game_view_.move(-1.0f * pos * zoom_level_);
                      panning_anchor_ = sf::Mouse::getPosition(game_->window_);
                  }
                  break;
              }
              case sf::Event::MouseButtonPressed: {
                  /* Start panning */
                  if(event.mouseButton.button == sf::Mouse::Middle) {
                      if(this->action_state_ != ActionState::PANNING) {
                          this->action_state_ = ActionState::PANNING;
                          this->panning_anchor_ = sf::Mouse::getPosition(game_->window_);
                      }
                  }
                  break;
              }
              case sf::Event::MouseButtonReleased: {
                  /* Stop panning */
                  if(event.mouseButton.button == sf::Mouse::Middle)
                      this->action_state_ = ActionState::NONE;
                  break;
              }
              /* Zoom the view */
              case sf::Event::MouseWheelMoved:
              {
                  if(event.mouseWheel.delta < 0) {
                      game_view_.zoom(2.0f);
                      zoom_level_ *= 2.0f;
                  }
                  else {
                      game_view_.zoom(0.5f);
                      zoom_level_ *= 0.5f;
                  }
                  break;
              }

              default: break;
          }
      }

      return;
  }

  GameStateEditor::GameStateEditor(Game* game)
  {
      zoom_level_ = 0.5f;
      game_ = game;
      sf::Vector2f pos = sf::Vector2f(game_->window_.getSize());
      gui_view_.setSize(pos);
      game_view_.setSize(pos);
      pos *= 0.5f;
      gui_view_.setCenter(pos);
      game_view_.zoom(zoom_level_);
      game_view_.setCenter(pos);


      map_ =  Map();
      map_.setHeight(64);
      map_.setWidth(64);
      map_.setTileSize(8);
      map_.empty(game_->tiles_);

      /* Centre the camera on the map */
      sf::Vector2f centre(map_.getWidth(), map_.getHeight() * 0.5);
      centre *= float( map_.getTileSize() );
      game_view_.setCenter(centre);

      this->action_state_ = ActionState::NONE;
  }

}
