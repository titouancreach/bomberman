#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "animationHandler.h"

namespace bomber {

enum class TileType { VOID, GROUND, WALL };

std::string tileTypeToStr(TileType type);

class Tile {

public:
  Tile();
  Tile(const unsigned int,
    const unsigned int,
    const std::vector<Animation>& animations,
    const TileType,
    sf::Texture &);
  virtual ~Tile();

  void draw(sf::RenderWindow&, float);
  void update();

  /* different variant for the same tile - graphically */
  int tile_variant_;

  /* get */
  const TileType& getType();
  sf::Sprite sprite_;

 private:
  animation::Handler animation_handler_;


  TileType type_;
  int flags_;


};

}
