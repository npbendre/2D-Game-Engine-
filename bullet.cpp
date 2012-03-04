#include "bullet.h"
using std::cout; using std::endl;
void Bullet::update(Uint32 ticks) {
 // std::cout << "entering bullet update" << endl;
  // Get the old x before the update:
  float x = X();
  Sprite::update(ticks);
  // Then get a new x to subtract from the old x:
  distance += fabs(x - X());
}
