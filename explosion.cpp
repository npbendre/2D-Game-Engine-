#include <iostream>
#include <cmath>

#include "explosion.h"

void Explosion::update(Uint32 ticks) { 
  float yincr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()- yincr );
  float xincr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()- xincr );
  distance += ( hypot(xincr, yincr) );
  if (distance > maxDistance) tooFar = true;
}

