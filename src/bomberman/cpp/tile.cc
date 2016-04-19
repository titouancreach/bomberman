#include <SFML/Graphics.hpp>

#include "tile.h"

namespace bomber {

/*!
   \brief Tile constructor
   \param tileSize size of the tile
   \param height of the tile
   \param animations list of animations
   \param tileType enum, type of the tile
   \param texture to draw
*/
Tile::Tile(const unsigned int tileSize,
  const unsigned int height,
  const std::vector<Animation>& animations,
  const TileType tileType,
  sf::Texture& texture) {

  type_ = tileType;
  tile_variant_ = 0;

  sprite_.setOrigin( sf::Vector2f(0.0f, tileSize*(height-1)) );
  sprite_.setTexture(texture);

  animation_handler_.setFrameSize( sf::IntRect(0, 0, tileSize*2, tileSize*height) );
  for(auto animation : animations) {
    animation_handler_.addAnimation(animation);
  }
  animation_handler_.update(0.0f);
}

Tile::Tile() {}
Tile::~Tile() {
}

/*!
   \brief Draw the tile to the window
   \param window SFML render window
   \param dt delta time
*/
void Tile::draw(sf::RenderWindow& window, float dt) {
  /* change the sprite to tile variant */
  animation_handler_.changeAnimation(tile_variant_);
  /* update animation */
  animation_handler_.update(dt);
  /* update sprite */
  sprite_.setTextureRect(animation_handler_.getBounds());
  /* draw the entity */
  window.draw(sprite_);
}

void Tile::update() {
  /* logic of a tile */
}

/* get */
const TileType& Tile::getType() {
  return type_;
}

/* set */

/*!
   \brief Enum to string
   \param type tile type
   \return enum string version
*/
std::string tileTypeToStr(TileType type)
{
    switch(type)
    {
        default:
        case TileType::VOID:            return "Void";
        case TileType::GROUND:          return "Ground";
        case TileType::WALL:            return "Wall";
    }
}

}
