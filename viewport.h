#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
#include "gamedata.h"

class Viewport {
public:
  static Viewport* getInstance();
  void update();

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }
  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }

  void setObjectToTrack(const Sprite *obj);
  const Sprite* getObjectToTrack() const { return objectToTrack; } 
  void freeze() { frozen = true; }
  void draw() const;

private:
  static Viewport  *instance;
  bool frozen;
  const Gamedata* gdata;
  Vector2f position;
  unsigned viewWidth;
  unsigned viewHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  Uint16 objWidth;
  Uint16 objHeight;
  
  const Sprite *objectToTrack;

  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
