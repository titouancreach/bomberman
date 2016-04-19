#include <SFML/Graphics.hpp>

#include "animation.h"

namespace bomber {

  Animation::Animation(unsigned int sf, unsigned int ef, float d) {
    start_frame_ = sf;
    end_frame_ = ef;
    duration_ = d;
  }

  unsigned int Animation::getLength() {
    return end_frame_ - start_frame_ + 1;
  }

}
