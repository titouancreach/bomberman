#include <iostream>

#include "app.h"

namespace bomber {

///
/// \brief Constructor of the application.
///
App::App()
  : window_({kResX, kResY, kBpp}, "Bomberman") {

  sf::Clock clock;
  sf::Time accumulator = sf::Time::Zero;
  sf::Time ups = sf::seconds(1.f / static_cast<float>(kMaxFps));

  while (window_.isOpen()) {

    ProcessInput();

    while (accumulator > ups) {
      accumulator -= ups;
      Update(ups);
    }

    Render();
    accumulator += clock.restart();
  }
}

///
/// \brief Process user input.
///
void App::ProcessInput() {
  sf::Event event;

  while (window_.pollEvent(event))
    if (event.type == sf::Event::Closed)
      window_.close();
}

///
/// \brief Update the application
/// \description each annimation or move must be
/// multiplied by delta to avoid lag.
/// \param delta Ellapsed time since the last frame
///
void App::Update(const sf::Time& delta) {
    std::cout << delta.asMilliseconds() << std::endl;
}

///
/// \brief Render the application.
///
void App::Render()
{
  window_.clear();

  for (auto& i: entities_)
    window_.draw(i);

  window_.display();
}

///
/// \brief Get drawable entities.
/// \return vector of the drawabale entities.
///
std::vector<sf::Drawable>& App::get_entities() {
  return entities_;
}

///
/// \brief Destructor of the application.
///
App::~App() {
}

}
