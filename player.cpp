#include "player.h"

void Player::right() { 
  if ( position[0] < WORLD_WIDTH-ballWidth) {
    velocity[0] = initialVelocity[0];
  }
} 
void Player::left()  { 
  if ( position[0] > 0) {
    velocity[0] = -initialVelocity[0]; 
  }
} 
void Player::up()    { 
  if ( position[1] > 0) {
    velocity[1] = -initialVelocity[1]; 
  }
} 
void Player::down()  { 
  if ( position[1] < WORLD_HEIGHT-ballHeight) {
    velocity[1] = initialVelocity[1]; 
  }
} 
