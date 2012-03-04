#include <list>
#include "sprite.h"
#include "gamedata.h"
#include "viewport.h"
#include "bullet.h"
#include "vector2f.h"

class Orbs {
public:
  Orbs();
  ~Orbs();
  void draw() const;
  void update(Uint32 ticks);
  int getTrackedOrb() const { return orbToTrack; }
  void setOrbToTrack(int) {
    Viewport::getInstance()->setObjectToTrack(*(orbs.begin()));
  }
  void updateOrbToTrack() {  
    Viewport::getInstance()->setObjectToTrack(*(orbs.begin()));
  }

 void shoot(int,int,int);
 int getScore() const { return score; } 
 int getBarLength() const {return bar_length; }

 Sprite* pter; 
 Sprite* pterLeft; 

private:
  Gamedata* gdata;
  std::list<Sprite*> orbs;
  std::list<Sprite*> orbsExplode;

  std::list<Sprite*> orbs1;
  std::list<Sprite*> orbsExplode1;


  std::list<Bullet*> bullets;
  std::list<Bullet*> bulletsExp;
  int score;
  int bar_length;

  int orbToTrack;
  void makeOrbs();
  int randomInRange(int a, int b) const;
  void manageCollisions();

  void makeBullet();
  void cullBullets();

  Orbs(const Orbs&);
  Orbs& operator=(const Orbs&);
};
