#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Explosion : public Sprite {
public:
  explicit Explosion(
    const Vector2f& pos, const Vector2f vel, const Frame* fm) :
    Sprite(pos, vel, fm), 
    distance(0), 
    maxDistance(Gamedata::getInstance()->getXmlInt("viewWidth")/2), 
    tooFar(false) 
  { }
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
private:
  float distance;
  float maxDistance;
  bool tooFar;
};
