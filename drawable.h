#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include "vector2f.h"

const int WORLD_WIDTH = 3000;
const int WORLD_HEIGHT = 720;

const int VIEW_WIDTH = 640;
const int VIEW_HEIGHT = 480;

// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(const Vector2f& pos, const Vector2f& vel) : 
    position(pos), velocity(vel), initialVelocity(vel) {}

  Drawable(const Drawable& s) : position(s.position), velocity(s.velocity),
    initialVelocity(s.velocity) { }

  virtual ~Drawable() {}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }

  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }

  float velocityX() const { return velocity[0]; }
  void velocityX(float vx) { velocity[0] = vx; }

  float velocityY() const { return velocity[1]; }
  void velocityY(float vy) { velocity[1] = vy; }
  const Vector2f& getPosition() const { return position; }
  const Vector2f& getVelocity() const { return velocity; }
  const Vector2f& getInitVelocity() const { return initialVelocity; }
  void setPosition(const Vector2f& pos) { position = pos; }
  void setVelocity(const Vector2f& vel) { velocity = vel; }
  void setInitVelocity(const Vector2f& vel) { initialVelocity = vel; }

float getVelocityx() const{
return initialVelocity[0];
}

void setInitialVelocityX(float vx) { initialVelocity[0] = vx; }
void setInitialVelocityY(float vy) { initialVelocity[1] = vy; }

float getVelocityy() const{
return initialVelocity[1];
}



private:
Vector2f position;
  Vector2f velocity;
  Vector2f initialVelocity;
  
};
#endif
