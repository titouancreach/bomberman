#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "tile.h"
#include "textureManager.h"

namespace bomber {

  class GameState;

  class Game {
  private:
    static const unsigned int kResX = 1280;
    static const unsigned int kResY = 720;
    static const unsigned int kMaxFps = 144;
    static const unsigned int kBpp = 64;

    static const unsigned int FrameRateLimit = 60;

    void loadTextures();
    void loadTiles();

  public:

    const static int kTileSize = 8;
    std::stack<GameState*> states_;

    sf::RenderWindow window_;

    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();

    void gameLoop();

    TextureManager texmgr_;
    sf::Sprite background;

    std::map<std::string, Tile> tiles_;

    Game();
    virtual ~Game();
  };

}
