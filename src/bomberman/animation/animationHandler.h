#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "animation.h"

namespace bomber::animation
{

class Handler {

public:

  /* add a new animation */
  void addAnimation(Animation &);
  /* update frame */
  void update(const float dt);
  /* Change the animation, resetting t in the process */
  void changeAnim(unsigned int animNum);

  /* Current section of the texture that should be displayed */
  sf::IntRect bounds;
  /* Pixel dimensions of each individual frame */
  sf::IntRect frameSize;

  Handler();
  Handler(const sf::IntRect& frameSize );

private:

  /* array of animation */
  std::vector<Animation> animations_;
  /* current time since animation started */
  float t_,
  /* current animation */
  int current_animation_;

};

}
