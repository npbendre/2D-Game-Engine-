#include "orbs.h"
#include "spriteFactory.h"
#include "explodingSprite.h"
#include "clock.h"

Orbs::Orbs() :
  gdata( Gamedata::getInstance() ),
  orbs( ),
  orbsExplode( ),
  orbs1( ),
  orbsExplode1( ),
  bullets( ),
  bulletsExp( ),
  score(0),
  bar_length(450),
  orbToTrack( 0 ) {
  makeOrbs();
  //Viewport::getInstance()->setObjectToTrack(orbs[0]);
}
	Orbs::~Orbs() { 
	std::list<Sprite*>::const_iterator ptr = orbs.begin();
	while(ptr!=orbs.end())
	{
  	delete (*ptr);
  	ptr++;
	}

	std::list<Sprite*>::const_iterator ptr1 = orbs1.begin();
	while(ptr1!=orbs1.end())
	{
  	delete (*ptr1);
  	ptr1++;
	}

	}


void Orbs::draw() const {

	std::list<Sprite*>::const_iterator ptr = orbs.begin();
	while(ptr!=orbs.end())
	{
  	(*ptr)->draw();
  	ptr++;
	}
	
	std::list<Sprite*>::const_iterator ptr1 = orbs1.begin();
	while(ptr1!=orbs1.end())
	{
  	(*ptr1)->draw();
  	ptr1++;
	}
	

std::list<Sprite*>::const_iterator ptrEx = orbsExplode.begin();
while(ptrEx!=orbsExplode.end())
{
  (*ptrEx)->draw();
  ptrEx++;
}

std::list<Sprite*>::const_iterator ptrEx1 = orbsExplode1.begin();
while(ptrEx1!=orbsExplode1.end())
{
  (*ptrEx1)->draw();
  ptrEx1++;
}


 for( std::list<Bullet*>::const_iterator bi = bullets.begin(); 
       bi != bullets.end(); ++bi ) {
    (*bi)->draw();
  }


}


void Orbs::update(Uint32 ticks) {
  std::list<Sprite*>::iterator ptr = orbs.begin();
 while(ptr!=orbs.end())
 {
  (*ptr)->update(ticks);
  ptr++;
 }

  std::list<Sprite*>::iterator ptrEx = orbsExplode.begin();
 while(ptrEx!=orbsExplode.end())
 {
  (*ptrEx)->update(ticks);
  ptrEx++;
  }


  std::list<Sprite*>::iterator ptr1 = orbs1.begin();
 while(ptr1!=orbs1.end())
 {
  (*ptr1)->update(ticks);
  ptr1++;
 }

  std::list<Sprite*>::iterator ptrEx1 = orbsExplode1.begin();
 while(ptrEx1!=orbsExplode1.end())
 {
  (*ptrEx1)->update(ticks);
  ptrEx1++;
  }


  cullBullets();

  for( std::list<Bullet*>::iterator bi = bullets.begin(); 
        bi != bullets.end(); ++bi ) {
     (*bi)->update( ticks );
    //cout << "updateing bullet" << endl;
   }

  std::list<Bullet*>::iterator bulletsptrEx = bulletsExp.begin();
 while(bulletsptrEx!=bulletsExp.end())
 {
  (*bulletsptrEx)->update(ticks);
  bulletsptrEx++;
  }
  manageCollisions();
 }

int Orbs::randomInRange(int a, int b) const {
  return (rand() % b) + a;
}

void Orbs::cullBullets() {
   std::list<Bullet*>::iterator bi = bullets.begin(); 
   while ( bi != bullets.end() ) {
     if ( (*bi)->getDistance() >= 200 ) {
       bi = bullets.erase(bi);
     }
     else ++bi;
   }
}



void Orbs::shoot(int pterX,int pterY,int dir) {
static int oldTicks = Clock::getInstance()->getTotalTicks();
  int ticks = Clock::getInstance()->getTotalTicks();
  if ( (ticks - oldTicks) < Gamedata::getInstance()->getXmlFloat("bulletDelay") ) return;
  oldTicks = ticks;
  int x = pterX;
  int y = pterY;
  int bulDirection = dir;
if(bulDirection==0)
{ 
bullets.push_back(new Bullet(Vector2f(x, y), Vector2f(Gamedata::getInstance()->getXmlFloat("bulletSpeed"),0),SpriteFrameFactory::getInstance()->getFrame("orb", "bullet")));
}
if(bulDirection==1)
{
bullets.push_back(new Bullet(Vector2f(x, y), Vector2f(Gamedata::getInstance()->getXmlFloat("bulletSpeed1"),0),SpriteFrameFactory::getInstance()->getFrame("orb", "bullet")));
}


 
}
void Orbs::makeOrbs() {
  unsigned maxOrbs = gdata->getXmlInt("orbsNumber");
  unsigned minX = gdata->getXmlInt("orbsMinX");
  unsigned maxX = gdata->getXmlInt("orbsMaxX");
  unsigned minY = gdata->getXmlInt("orbsMinY");
  unsigned maxY = gdata->getXmlInt("orbsMaxY");
  unsigned minXspeed = gdata->getXmlInt("orbsMinXspeed");
  unsigned maxXspeed = gdata->getXmlInt("orbsMaxXspeed");
  unsigned minYspeed = gdata->getXmlInt("orbsMinYspeed");
  unsigned maxYspeed = gdata->getXmlInt("orbsMaxYspeed");

  orbs.push_back( new Sprite(
    Vector2f(randomInRange(minX, maxX), randomInRange(minY, maxY)),
    Vector2f(randomInRange(maxXspeed, maxXspeed+100), 
             randomInRange(minYspeed, maxYspeed)),
    SpriteFrameFactory::getInstance()->getFrame("orb", "cyanOrb")));

  orbs.push_back( new Sprite(
    Vector2f(randomInRange(minX, maxX), randomInRange(minY, maxY)),
    Vector2f(randomInRange(maxXspeed, 2*maxXspeed+200), 
             randomInRange(minYspeed, maxYspeed)),
    SpriteFrameFactory::getInstance()->getFrame("orb", "greenOrb")));

  for (unsigned i = 0; i < maxOrbs; ++i) {
    orbs.push_back( new Sprite(
      Vector2f(randomInRange(minX, maxX), randomInRange(minY, maxY)),
      Vector2f(randomInRange(minXspeed, maxXspeed), 
               randomInRange(minYspeed, maxYspeed)),
      SpriteFrameFactory::getInstance()->getFrame("orb", "yellowOrb")));
	  }

   for (unsigned i = 0; i < maxOrbs; ++i) {
    orbs1.push_back( new Sprite(
      Vector2f(randomInRange(minX, maxX), randomInRange(minY, maxY)),
      Vector2f(randomInRange(minXspeed, maxXspeed), 
               randomInRange(minYspeed, maxYspeed)),
      SpriteFrameFactory::getInstance()->getFrame("orb", "yellowOrb1")));
	  }

}


 void Orbs::manageCollisions(){
  std::list<Sprite*>::iterator ptr = orbs.begin();
  std::list<Sprite*>::iterator ptr1 = orbs1.begin();

  std::list<Bullet*>::iterator bulletptr = bullets.begin();
  
  int flag=0;
  //Bullet* tempBullet = *bulletptr;
  //Sprite* tempNew = *ptr;
  
  while(bulletptr!=bullets.end())
  { 

	//white ghosts
  	while(ptr!=orbs.end())
	{
            Bullet* tempBullet = *bulletptr;
		flag=0;
  		if(tempBullet->manageCollision(*ptr))
  	        { 
                	//std::cout  << "enterning the if loop" << std::endl;
     	           	int n = gdata->getXmlInt("orbChunks");
     	          	orbsExplode.push_back(new ExplodingSprite(*(*ptr), n));
     	          	delete(*ptr);
     	           	ptr = orbsExplode.erase(ptr);
     	          	delete(*bulletptr);
                        bulletptr=bulletsExp.erase(bulletptr);
                        flag=1; 
			score++;
			break;   
                }
                else { 
                    	ptr++;
                }
	}
	if(flag==0)
		bulletptr++;
  }

  
  

   

   while(ptr1!=orbs1.end())
   {
	    Sprite* ptr2 = pter;
	    Sprite* ptrLeft = pterLeft;

            //Bullet* tempBullet = *bulletptr;
	    flag=0;
  	    if(ptr2->manageCollision(*ptr1) || ptrLeft->manageCollision(*ptr1))
  	        { 
                	
     	           	int n = gdata->getXmlInt("orbChunks");
     	          	orbsExplode1.push_back(new ExplodingSprite(*(*ptr1), n));
     	          	delete(*ptr1);

     	           	ptr1 = orbsExplode1.erase(ptr1);

     	          	if(bar_length>0)
				bar_length -= 75;
			
			break;   
                }
                else { 
                    	ptr1++;
                }
	}


  


}



