#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>

// The only class that can use the clock is Manager, and
// in Manager there can be only one clock:
//class Manager;

class Clock {
public:
  friend class Manager;
  static Clock* getInstance();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
  unsigned getTotalTicks() const;
  Clock& operator++();
  Clock  operator++(int);
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned getFrames() const  { return frames;  }
  unsigned getSeconds() const { return getTotalTicks()/1000;  }
  float getFps() const;
  unsigned getElapsedTicks();
  void resetFps() { frames = 0; timeAtStart = 0; }

  void start();
  void pause();
  void unpause();
  void debug();
  //void save(std::fstream& xmlfile) const;
  //void restore(const std::string& filename);
private:
  static Clock* instance;

  bool started;
  bool paused;
  unsigned frames;
  unsigned timeAtStart;
  unsigned timeAtPause;
  unsigned currTicks;
  unsigned prevTicks;
  unsigned ticks;

  Clock();
};
