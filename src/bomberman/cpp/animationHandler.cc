#include "animationHandler.h"

namespace bomber { namespace animation {

/*!
   \brief Animation Handler default constructor
*/
Handler::Handler() {
  t_ = 0.0f;
  current_animation_ = -1;
}

/*!
   \brief Animation Handler constructor
   \param fs Frame size
   \return "Return of the function"
*/
Handler::Handler(const sf::IntRect& fs) {
  t_ = 0.0f;
  current_animation_ = -1;
  frame_size_ = fs;
}

/* get */
sf::IntRect Handler::getBounds() {
  return bounds_;
}
sf::IntRect Handler::getFrameSize() {
  return frame_size_;
}

/* set */

/*!
   \brief Set the frame size
   \param v value of the new frame size
*/
void Handler::setFrameSize(sf::IntRect v) {
  frame_size_ = v;
}


/*!
   \brief Addd animation to vector
   \param item animation item
*/
void Handler::addAnimation(Animation& item) {
  /* add the item to vector */
  animations_.push_back(item);
}

/*!
   \brief Change current animation
   \param idx index of the animation
*/
void Handler::changeAnimation(unsigned int idx) {

  /* can't change if doesn't exist or if active */
  if (current_animation_ == idx || idx >= animations_.size() || idx < 0) return;
  /* set */
  current_animation_ = idx;
  /* update bounds */
  sf::IntRect rect = frame_size_;
  rect.top = rect.height * idx;
  bounds_ = rect;
  t_ = 0.0;
}

/*!
   \brief Update animation, moving to next frame accordingly to dt
   \param  dt delta t
*/
void Handler::update(const float dt) {

  if (current_animation_ >= animations_.size() || current_animation_ < 0) return;

  float duration = animations_[current_animation_].getDuration();

  /* if we need to move to next frame */
  if ( int((t_+dt) / duration) > int(t_ / duration) ) {
      /* calculate frame number */
      int frame = int((t_ + dt) / duration);

      /* adjust for looping */
      frame %= animations_[current_animation_].getLength();

      /* Set the sprite to the new frame */
      sf::IntRect rect = frame_size_;

      rect.left = rect.width * frame;
      rect.top = rect.height * current_animation_;

      bounds_ = rect;
  }

  /* time elapsed */
  this->t_ += dt;
  /* looping */
  if(this->t_ > duration * animations_[current_animation_].getLength() ) {
      this->t_ = 0.0f;
  }
}


}}
