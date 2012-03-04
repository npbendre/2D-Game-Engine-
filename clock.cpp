#include <iostream>
#include <map>
#include <sstream>
using std::cout; using std::endl;
#include "clock.h"
using std::cout; using std::endl;

Clock* Clock::getInstance() {
  if (!instance) instance = new Clock(); 
  return instance;
}

Clock::Clock() :
  started(false), 
  paused(false), 
  frames(0), 
  timeAtStart(0), timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0) 
  {
  start();
}

Clock::Clock(const Clock& c) :
  started(c.started), 
  paused(c.paused), frames(c.frames), 
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks) 
  {
  start();
}

void Clock::debug( ) { 
  cout << "The clock is:" << endl;
  cout << "\tstarted:" << started << endl;
  cout << "\tpaused:" << paused << endl;
  cout << "\tframes:" << frames << endl;
  cout << "\ttimeAtStart:" << timeAtStart << endl;
  cout << "\ttimeAtPause:" << timeAtPause << endl;
  cout << "\tcurrTicks:" << currTicks << endl;
  cout << "\tprevTicks:" << prevTicks << endl;
  cout << "\tticks:" << ticks << endl;
  cout << endl;
}

unsigned Clock::getTotalTicks() const { 
  if (paused) return timeAtPause;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned Clock::getElapsedTicks() { 
  if (paused) return 0;
  currTicks = getTotalTicks();
  ticks = currTicks-prevTicks;
  prevTicks = currTicks;
  return ticks;
}

float Clock::getFps() const { 
  static unsigned seconds = getSeconds();
  static float fps = 0;
  if ( getSeconds() > 0 && getSeconds() > seconds) {
    seconds = getSeconds();
    fps = frames/seconds;
    return frames/getSeconds();  
  }
  else if ( getSeconds() > 0 ) return fps;
  else {
    fps = 0;
    return 0;
  }
}

Clock& Clock::operator++() { 
  if ( !paused ) ++frames; 
  return *this;
}
Clock  Clock::operator++(int) { 
  if ( !paused ) frames++; 
  return *this;
}

void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks(); 
}
void Clock::pause() {
  if( started && !paused ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}

