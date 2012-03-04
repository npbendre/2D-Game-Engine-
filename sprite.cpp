#include <iostream>
#include "sprite.h"
#include "gamedata.h"
#include "collisionStrategy.h"

const Vector2f WALL_LEFT = Vector2f(-1, 0);
const Vector2f WALL_RIGHT = Vector2f(1, 0);
const Vector2f WALL_TOP = Vector2f(0, 1);
const Vector2f WALL_BOTTOM = Vector2f(0, -1);

Sprite::Sprite(const Vector2f& pos, const Vector2f vel, const Frame* fm) :
  Drawable(pos, vel), 
  frame(fm),
  strategy( NULL )
{ 
  if ( Gamedata::getInstance()->getXmlStr("orbCollisionStrategy") ==
       "RectangularCollisionStrategy") {
    strategy = new RectangularCollisionStrategy;
  }
  else if ( Gamedata::getInstance()->getXmlStr("orbCollisionStrategy") ==
       "MidPointCollisionStrategy") {
    strategy = new MidPointCollisionStrategy;
  }
  else strategy = new PerPixelCollisionStrategy;
}

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getPosition(), s.getVelocity()), 
  frame(s.frame),
  strategy(s.strategy)
  { }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setInitVelocity(rhs.getInitVelocity());
  frame = rhs.frame;
  strategy = rhs.strategy;
  return *this;
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

unsigned Sprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}


int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

bool Sprite::manageCollision(Sprite *obj) { 
  if ( !strategy->execute(*this, *obj) ) return false;
  int widthSum = frame->getWidth()/2 + obj->getFrame()->getWidth()/2; 
  if ( getDistance(obj) <= widthSum ) {
    Vector2f velocity = getVelocity() - obj->getVelocity();
    Vector2f distance = getPosition() - obj->getPosition();
    if ( velocity.dot(distance) < 0 ) {
      distance = distance.normalize();
      Vector2f v1 = getVelocity();
      v1 -= 2 * distance * getVelocity().dot(distance);
      setVelocity(v1);
      Vector2f v2 = obj->getVelocity();
      v2 -= 2 * distance * obj->getVelocity().dot(distance);
      obj->setVelocity(v2);
    } // end of inner if
  } // end of outer if
return true;
}


void Sprite::update(Uint32 ticks) { 
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  float height = static_cast<float>(frame->getHeight());
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > Gamedata::getInstance()->getXmlInt("worldHeight")-height) {
    velocityY( -abs( velocityY() ) );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frame->getWidth());
  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth")-width) {
    velocityX( -abs( velocityX() ) );
  }
}
