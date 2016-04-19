#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "animation.h"

namespace bomber { namespace animation {

class Handler {

public:

  /* add a new animation */
  void addAnimation(Animation &);
  /* update frame */
  void update(const float dt);
  /* Change the animation, resetting t in the process */
  void changeAnimation(unsigned int animNum);

  /* get */
  sf::IntRect getBounds();
  sf::IntRect getFrameSize();

  /* set */
  void setFrameSize(sf::IntRect);

  /* constructors */
  Handler();
  Handler(const sf::IntRect& frameSize );

private:

  /* array of animation */
  std::vector<Animation> animations_;
  /* current time since animation started */
  float t_;
  /* current animation */
  unsigned int current_animation_;

  /* Current section of the texture that should be displayed */
  sf::IntRect bounds_;
  /* Pixel dimensions of each individual frame */
  sf::IntRect frame_size_;
};

}}
