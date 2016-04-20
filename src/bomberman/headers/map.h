#pragma once

#include <vector>

#include "tile.h"

namespace bomber {

class Map {

 public:
  Map();
  Map(const std::string& filename, unsigned int width, unsigned int height,
    std::map<std::string, Tile>& tiles);

  virtual ~Map();

  /* load from disk */
  void load(const std::string& filename, unsigned int width,
    unsigned int height, std::map<std::string, Tile>& tiles);

  /* save to disk */
  void save(const std::string& filename);

  /* draw to window */
  void draw(sf::RenderWindow& window, float dt);

  /* create random map */
  void randomize(std::map<std::string, Tile>& tiles);
  /* create empty map */
  void empty(std::map<std::string, Tile>& tiles);

  /* get */
  unsigned int getHeight() const;
  unsigned int getWidth() const;
  unsigned int getTileSize() const;

  /* set */
  void setHeight(unsigned int);
  void setWidth (unsigned int);
  void setTileSize(unsigned int);

 private:
  Tile **data_;
  unsigned int height_;
  unsigned int width_;

  /* tiles related */
  std::vector<Tile> tiles_;
  unsigned int tile_size_;
  unsigned int num_regions_[1];

};

}
