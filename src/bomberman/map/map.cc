#include "map.h"

namespace bomber {

Map::Map() {
  tile_size_ = 8;
  width_ = 0;
  height_ = 0;
  num_regions_[0] = 1;
}

Map::Map(const std::string& filename, unsigned int width, unsigned int height) {
  this->tile_size_ = 8;
  load(filename, width, height);
}

Map::~Map() {
}

}
