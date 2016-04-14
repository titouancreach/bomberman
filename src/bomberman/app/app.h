#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"

namespace bomber {

class App {

 public:
  static const unsigned int kResX = 1280;
  static const unsigned int kResY = 720;
  static const unsigned int kMaxFps = 144;
  static const unsigned int kBpp = 64;

  std::vector<sf::Drawable*>& get_entities();

  App();
  virtual ~App();

 private:

  void ProcessInput();
  void Update(const sf::Time& delta);
  void Render();

  sf::RenderWindow window_;
  std::vector<sf::Drawable*> entities_;

  Map map_;

};

}
