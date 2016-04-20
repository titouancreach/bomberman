#include <iostream>
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
                if( action_state_ == ActionState::PANNING ) {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(game_->window_) - panning_anchor_);
                    game_view_.move(-1.0f * pos * zoom_level_);
                    panning_anchor_ = sf::Mouse::getPosition(game_->window_);
                }
                /* Select tiles */
                else if(action_state_ == ActionState::SELECTING)
                {
                    sf::Vector2f pos = game_->window_.mapPixelToCoords(sf::Mouse::getPosition(game_->window_), game_view_);
                    selection_end_.x = pos.y / (map_.getTileSize()) + pos.x / (2*map_.getTileSize()) - map_.getWidth() * 0.5 - 0.5;
                    selection_end_.y = pos.y / (map_.getTileSize()) - pos.x / (2*map_.getTileSize()) + map_.getWidth() * 0.5 + 0.5;

                    map_.clearSelected();
                    if(current_tile_->getType() == TileType::GROUND)
                    {
                        map_.select(selection_start_, selection_end_, {current_tile_->getType(), TileType::WALL});
                    }
                    else
                    {
                        map_.select(selection_start_, selection_end_,
                        {
                            current_tile_->getType(), TileType::WALL
                        });
                    }
                }
                break;
            }
            case sf::Event::MouseButtonPressed: {
                /* Start panning */
                if(event.mouseButton.button == sf::Mouse::Middle) {
                    if(action_state_ != ActionState::PANNING) {
                        action_state_ = ActionState::PANNING;
                        panning_anchor_ = sf::Mouse::getPosition(game_->window_);
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Left)
                {
                    /* Select map tile */
                    if(action_state_ != ActionState::SELECTING)
                    {
                        action_state_ = ActionState::SELECTING;
                        sf::Vector2f pos = game_->window_.mapPixelToCoords(sf::Mouse::getPosition(game_->window_), game_view_);
                        selection_start_.x = pos.y / (map_.getTileSize()) + pos.x / (2*map_.getTileSize()) - map_.getWidth() * 0.5 - 0.5;
                        selection_start_.y = pos.y / (map_.getTileSize()) - pos.x / (2*map_.getTileSize()) + map_.getWidth() * 0.5 + 0.5;
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    /* Stop selecting */
                    if(action_state_ == ActionState::SELECTING)
                    {
                        action_state_ = ActionState::NONE;
                        map_.clearSelected();
                    }
                }

                break;
            }
            case sf::Event::MouseButtonReleased: {
                /* Stop panning */
                if(event.mouseButton.button == sf::Mouse::Middle)
                    action_state_ = ActionState::NONE;
                /* Stop selecting */
                else if(event.mouseButton.button == sf::Mouse::Left) {
                    if(action_state_ == ActionState::SELECTING) {
                        action_state_ = ActionState::NONE;
                        map_.clearSelected();
                    }
                }
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

GameStateEditor::GameStateEditor(Game* game) {

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

  selection_start_ = sf::Vector2u(0, 0);
  selection_end_ = sf::Vector2u(0, 0);

  current_tile_ = &game_->tiles_.at("wall");

  action_state_ = ActionState::NONE;
}

}
