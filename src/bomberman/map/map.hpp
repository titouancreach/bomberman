#pragma once

#include "../tile/tile.hpp"

namespace Bomber {

    class Map {

    public:
        Map();
        virtual ~Map();

    private:
        Tile **data_;
        
    };

}
