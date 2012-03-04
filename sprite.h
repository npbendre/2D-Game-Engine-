#ifndef SPRITE__H
#define SPRITE__H

#include <string>
using std::string;
#include <iostream>

#include "drawable.h"
#include "frame.h"

class CollisionStrategy;
class Sprite : public Drawable {
public:
  Sprite(const Vector2f& pos, const Vector2f vel, const Frame* fm);
  Sprite(const Sprite& s);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  unsigned getPixel(Uint32, Uint32) const;

  bool manageCollision(Sprite*);
  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }

protected:
  const Frame * frame;
  CollisionStrategy* strategy;
  int getDistance(const Sprite*) const;
};
#endif
