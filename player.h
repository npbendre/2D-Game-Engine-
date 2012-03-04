#include "sprite.h"

class Player : public Sprite {
public:
  Player(Vector2f pos, Vector2f vel, Frame* f) : 
    Sprite(pos, vel, f), 
    ballWidth( f->getWidth() ), ballHeight( f->getWidth() )
  {}

  virtual void update() { Sprite::update(); }

  void stop() { velocity = Vector2f(0, 0); }
  void right();
  void left();
  void up();
  void down();

private:
  float ballWidth;
  float ballHeight;
};

