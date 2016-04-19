#include <vector>
#include <map>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "map.h"

namespace bomber {

Map::Map() {
  tile_size_ = 8;
  width_ = 0;
  height_ = 0;
  num_regions_[0] = 1;
}

Map::Map(const std::string& filename, unsigned int width, unsigned int height,
  std::map<std::string, Tile> &tiles) {
  this->tile_size_ = 8;
  load(filename, width, height, tiles);
}

void Map::load(const std::string& filename, unsigned int width,
  unsigned int height, std::map<std::string, Tile>& tiles ) {

  std::ifstream iFile;

  iFile.open(filename, std::ios::in | std::ios::binary);
  width_ = width;
  height_ = height;

  for (unsigned int pos = 0; pos < width_ * height_; ++pos) {

    TileType tileType;

    iFile.read((char*)&tileType, sizeof(int));
    switch (tileType) {
      case TileType::VOID:
        break;
      case TileType::GROUND:
        tiles_.push_back( tiles.at("ground") );
        break;
      case TileType::WALL:
        tiles_.push_back( tiles.at("wall") );
        break;
      default:
        break;
    }

    Tile& tile = tiles_.back();
    iFile.read((char*)&tile.tile_variant_, sizeof(int));
//    iFile.read((char*)&tile.regions, sizeof(int)*1);

  }

  iFile.close();
}

void Map::save(const std::string& filename) {
  std::ofstream oFile;

  oFile.open(filename, std::ios::out | std::ios::binary);

  for (auto tile : tiles_) {
    oFile.write((char*)&tile.getType(), sizeof(int));
    oFile.write((char*)&tile.tile_variant_, sizeof(int));
  }

  oFile.close();
}

void Map::draw(sf::RenderWindow& window, float dt) {
  for (unsigned int y = 0; y < height_; ++y) {
    for (unsigned int x = 0; x < width_; ++x) {

      sf::Vector2f pos;

      pos.x = (x - y) * tile_size_ + width_ * tile_size_;
      pos.y = (x + y) * tile_size_ * 0.5;

      /* set pos */
      tiles_[y * width_ + x].sprite_.setPosition(pos);
      /* draw the tile */
      tiles_[y * width_ + x].draw(window, dt);

    }
  }
}

Map::~Map() {
}

}
