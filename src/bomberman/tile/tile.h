#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "animationHandler.h"

namespace bomber {

enum class TileType { VOID, GROUND, WALL };

std::string tileTypeToStr(TileType type);

class Tile {

public:
  Tile(const unsigned int,
    const unsigned int,
    const std::vector<Animation>& animations,
    const TileType,
    sf::Texture &);
  virtual ~Tile();

  void draw(sf::RenderWindow&, float);
  void update();

 private:
  animation::Handler animation_handler_;


  int flags_;
  sf::Sprite sprite_;
  TileType type_;

  /* different variant for the same tile - graphically */
  int tile_variant_;

};

}
