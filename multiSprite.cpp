#include "multiSprite.h"
using std::cout; using std::endl;

void MultiSprite::advanceFrame(Uint32 ticks) {
  static float ms = 1000.0/frameInterval;
  static float dt = 0;
  dt += ticks;
  int df = dt / ms;
  dt -= df * ms;
  currentFrame = (currentFrame + df) % numberOfFrames;
}

void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  // If we're okay with the default behavior, We could just use 
  // the update in sprite, which means we use this one to advance
  // the frame (possibly), and then use the update in Sprite.
  // For an example of this, look in collisions, pter.

  // Here, we make Pter wrap around the screen:
  float height = static_cast<float>(frame->getHeight());
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  if ( Y() < 0) {
    Y( Gamedata::getInstance()->getXmlInt("worldHeight") );
  }
  if ( Y() > Gamedata::getInstance()->getXmlInt("worldHeight")-height) {
    Y( -height );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frame->getWidth());
  if ( X() + width < 0) {
    X( Gamedata::getInstance()->getXmlInt("worldWidth") );
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth") ) {
    X( -width );
  }
}


void MultiSprite::right() { 
positionright=getPosition(); 
velocityX(abs(getVelocityx())); 
}

void MultiSprite::left() {
positionleft=getPosition(); 
velocityX(-abs(getVelocityx()));
}

void MultiSprite::up() { 
  velocityY(-abs(getVelocityy()));
  position=getPosition(); 
}

void MultiSprite::down() {
  velocityY(abs(getVelocityy()));
  position=getPosition(); 
}


