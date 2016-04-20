#include <vector>
#include <map>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "map.h"

namespace bomber {

Map::Map() {
  num_selected_ = 0;
  tile_size_ = 8;
  width_ = 0;
  height_ = 0;
  num_regions_[0] = 1;
}

Map::Map(const std::string& filename, unsigned int width, unsigned int height,
  std::map<std::string, Tile> &tiles) {

  num_selected_ = 0;
  tile_size_ = 8;
  load(filename, width, height, tiles);
}

void Map::load(const std::string& filename, unsigned int width,
  unsigned int height, std::map<std::string, Tile>& tiles ) {

  std::ifstream iFile;

  iFile.open(filename, std::ios::in | std::ios::binary);
  width_ = width;
  height_ = height;

  for (unsigned int pos = 0; pos < width_ * height_; ++pos) {

    selected_.push_back(0);

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

      /* Change the color if the tile is selected */
      if(selected_[y*width_+x])
          tiles_[y*width_+x].sprite_.setColor(sf::Color(0x7d, 0x7d, 0x7d));
      else
          tiles_[y*width_+x].sprite_.setColor(sf::Color(0xff, 0xff, 0xff));

      /* draw the tile */
      tiles_[y * width_ + x].draw(window, dt);

    }
  }

}

void Map::clearSelected() {
    for(auto& tile : selected_) tile = 0;
    num_selected_ = 0;
    return;
}

void Map::select(sf::Vector2u start, sf::Vector2u end, std::vector<TileType> blacklist){
  /* Swap coordinates if necessary */
  if(end.y < start.y) std::swap(start.y, end.y);
  if(end.x < start.x) std::swap(start.x, end.x);

  /* Clamp in range */
  if(end.x >= width_)       end.x = width_ - 1;
  else if(end.x < 0)        end.x = 0;
  if(end.y >= height_)      end.y = height_ - 1;
  else if(end.y < 0)        end.y = 0;
  if(start.x >= width_)     start.x = width_ - 1;
  else if(start.x < 0)      start.x = 0;
  if (start.y >= height_)   start.y = height_ - 1;
  else if(start.y < 0)      start.y = 0;

  for(unsigned int y = start.y; y <= end.y; ++y) {
      for(unsigned int x = start.x; x <= end.x; ++x) {
          /* Check if the tile type is in the blacklist. If it is, mark it as
           * invalid, otherwise select it */
          selected_[y*width_+x] = 1;
          ++num_selected_;
          for(auto type : blacklist)
          {
              if( tiles_[y*width_+x].getType() == type )
              {
                  selected_[y*width_+x] = 2;
                  --num_selected_;
                  break;
              }
          }
      }
  }

  return;
}

/*!
   \brief Creates an empty map
   \param tiles tiles atlas
*/
void Map::empty(std::map<std::string, Tile>& tiles) {
  Animation staticAnimation(0, 0, 1.0f);


  /* side */
  for (unsigned int x = 0; x < width_ ; ++x) {
    selected_.push_back(0);
    tiles_.push_back( tiles.at("wall") );
  }

  /* inside */
  for (unsigned int y = 1; y < height_ - 1; ++y) {
    selected_.push_back(0);
    tiles_.push_back( tiles.at("wall") );

    for (unsigned int x = 1; x < width_ - 1; ++x) {
      selected_.push_back(0);
      tiles_.push_back( tiles.at("ground") );
    }
    selected_.push_back(0);
    tiles_.push_back( tiles.at("wall") );
  }

  /* side */
  for (unsigned int x = 0; x < width_ ; ++x) {
    selected_.push_back(0);
    tiles_.push_back( tiles.at("wall") );
  }
}

/*!
   \brief Creates random map
   \param tiles tiles atlas
*/
void Map::randomize(std::map<std::string, Tile>& tiles) {
  Animation staticAnimation(0, 0, 1.0f);

  for (unsigned int y = 0; y < height_; ++y) {
    for (unsigned int x = 0; x < width_; ++x) {

      /*** random ***/
     double ix = rand()/static_cast<double>(RAND_MAX+1);
     // [0,1[ * (max - min) + min is in [min,max[
     int r = 1 + static_cast<int>( ix * (3 - 1) );
     /** end random **/

     if ( r == 0 ) {
       tiles_.push_back( tiles.at("wall") );
     }
     else if (r==1) {
       tiles_.push_back( tiles.at("ground") );
     }

    }
  }
}

/* getters */
unsigned int Map::getHeight()   const { return height_;    }
unsigned int Map::getWidth()    const { return width_;     }
unsigned int Map::getTileSize() const { return tile_size_; }

/* setters */
void Map::setHeight(unsigned int v)   { height_    = v; }
void Map::setWidth(unsigned int v)    { width_     = v; }
void Map::setTileSize(unsigned int v) { tile_size_ = v; }

/* destructor */
Map::~Map() {}

}
