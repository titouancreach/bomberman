#pragma once

#include "tile.h"

namespace bomber {

class Map {

 public:
  Map();
  virtual ~Map();

 private:
  Tile **data_;

};

}
