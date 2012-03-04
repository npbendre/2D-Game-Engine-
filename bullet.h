#include <cmath>
#include "sprite.h"

// A bullet is a sprite that tracks distance
// A bullet has a definite lifetime

class Bullet : public Sprite {
public:
  Bullet(const Vector2f& pos, const Vector2f& vel, const Frame * f) :
    Sprite(pos, vel, f), 
    distance(0) 
  {}
  void update(Uint32 ticks);
  float getDistance() const { return distance; }
  void setDistance(float d) { distance = d; }
private:
  Bullet();
  float distance;
};
