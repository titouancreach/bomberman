#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace bomber
{

class Animation {

public:

  Animation(unsigned int startFrame, unsigned int endFrame, float duration);

  unsigned int getLength();

private:
  unsigned int start_frame_;
  unsigned int end_frame_;

  float duration_;
};


}
