#include <SDL.h>
#include <iostream>
using std::cout; using std::endl; 
#include <vector>
#include <string>
using std::string; using std::cout;

#include "ioManager.h"
#include "world.h"
#include "multiSprite.h"
#include "clock.h"
#include "orbs.h"
#include "gui.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void toggleTheStupidHud() { 
drawTheStupidHud = not drawTheStupidHud; 
}

private:
  bool env;
  const Gamedata* gdata;
  bool drawTheStupidHud;
  IOManager *io;
  Clock clock;
  SDL_Surface *screen;

  World clouds;
  World hills;
  World ghostbcknd;
  Viewport *view;
  Sprite* pter;
  Sprite* pterleft;
  int var1;
  int var2;
  Gui gui;
  int remainingTime; 
  Orbs orbs;
  


  void draw() const;
  void update();
  void drawHud() const;
  void drawBackground() const;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
