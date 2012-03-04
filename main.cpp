// Brian Malloy        Game Construction

#include "manager.h"
#include "spriteFactory.h"
#include "multiSpriteFactory.h"
IOManager *IOManager::instance = NULL;
Gamedata* Gamedata::instance = NULL;
SpriteFrameFactory* SpriteFrameFactory::instance = NULL;
MultiSpriteFrameFactory* MultiSpriteFrameFactory::instance = NULL;
Clock* Clock::instance = NULL;
Viewport* Viewport::instance = NULL;

int main(int, char*[]) {
   try {
      Manager game_manager;
      game_manager.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
