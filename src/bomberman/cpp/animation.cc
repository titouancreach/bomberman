#include <SFML/Graphics.hpp>

#include "animation.h"

namespace bomber {

  /*!
     \brief Animation constructor
     \param sf start frame
     \param ed end frame
     \param d duration
  */
  Animation::Animation(unsigned int sf, unsigned int ef, float d) {
    start_frame_ = sf;
    end_frame_ = ef;
    duration_ = d;
  }

  /*!
     \brief calculates length of the animation
     \return length of the animation
  */
  unsigned int Animation::getLength() {
    return end_frame_ - start_frame_ + 1;
  }


  /*!
     \brief Start frame getter
     \return start frame index
  */
  unsigned int Animation::getStartFrame() {
    return start_frame_;
  }
  /*!
     \brief End frame getter
     \return  end frame index
  */
  unsigned int Animation::getEndFrame() {
    return end_frame_;
  }
  /*!
     \brief Durationg getter
     \return duration
  */
  float Animation::getDuration() {
    return duration_;
  }


}
