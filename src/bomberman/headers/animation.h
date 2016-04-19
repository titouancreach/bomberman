#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace bomber
{

class Animation {

public:

  /* constructors */
  Animation(unsigned int startFrame, unsigned int endFrame, float duration);

  /* calculates and returns length */
  unsigned int getLength();

  /* getters */
  unsigned int getStartFrame();
  unsigned int getEndFrame();
  float getDuration();


private:

  unsigned int start_frame_;
  unsigned int end_frame_;

  float duration_;
};


}
