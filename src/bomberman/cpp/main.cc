#include "game.h"
#include "gameStateStart.h"
//#include "app.h"

int main() {
//  bomber::App app;

  bomber::Game game;

  game.pushState( new bomber::GameStateStart(&game) );
  game.gameLoop();

  return 0;
}
