#include "animationHandler.h"

namespace bomber::animation {

/*!
   \brief Animation Handler default constructor
*/
Handler::Handler() {
    t_. = 0.0f;
    current_animation_ = -1;
}

/*!
   \brief Animation Handler constructor
   \param fs Frame size
   \return "Return of the function"
*/
Handler::Handler(const sf::IntRect& fs) {
    t_. = 0.0f;
    current_animation_ = -1;
    frameSize = fs;
}

}
