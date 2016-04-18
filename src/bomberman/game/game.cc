#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#include "game.h"
#include "gameState.h"

namespace bomber {

  void Game::pushState(GameState* state) {
    states_.push(state);
  }

  void Game::popState() {
    delete states_.top();
    states_.pop();
  }

  void Game::changeState(GameState* state) {
    if(!states_.empty())
      popState();
    pushState(state);
  }

  GameState* Game::peekState() {
    if (states_.empty())
      return nullptr;
    return states_.top();
  }

  void Game::gameLoop() {
    sf::Clock clock;

    while (window_.isOpen()) {

      sf::Time elapsed = clock.restart();
      float dt = elapsed.asSeconds();

      if (peekState() == nullptr) continue;

      peekState()->handleInput();
      peekState()->update(dt);

      window_.clear(sf::Color::Black);
      peekState()->draw(dt);
      window_.display();
    }
  }

  Game::Game()
    : window_({kResX, kResY, kBpp}, "Bomberman") {
      window_.setFramerateLimit(60);
  }

  Game::~Game() {
    while (!states_.empty()) {
      popState();
    }
  }

}
