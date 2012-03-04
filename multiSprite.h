#include <iostream>
#include "sprite.h"
#include "gamedata.h"
//change
#include "vector2f.h"

class MultiSprite : public Sprite {
public:
  MultiSprite(const Vector2f& pos, const Vector2f vel, 
              const Frame* fm, const string& name) : 
    Sprite(pos, vel, fm),
   positionleft(0,0),
positionright(0,0),
 position(0,0),
    currentFrame(0),
    numberOfFrames( Gamedata::getInstance()->getXmlInt(name+"Frames") ),
    frameInterval(Gamedata::getInstance()->getXmlInt(name+"FrameInterval"))
  {}

 virtual void update() { MultiSprite::update(); }

  
  void right();
  void left();
  void up(); 
  void down();
  

  virtual const Frame* getFrame() const { return &frame[currentFrame]; }
  void draw() const { frame[currentFrame].draw(X(), Y()); }
  virtual void update(Uint32 ticks);
  
 Vector2f positionleft;
Vector2f positionright;
 Vector2f position;

private:
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;

  void advanceFrame(Uint32 ticks);
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&);
};
