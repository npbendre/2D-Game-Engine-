#include <cmath>
#include "manager.h"
#include "spriteFactory.h"
#include "multiSpriteFactory.h"
#include "explodingSprite.h"
//change sound
#include "sound.h"
#include "SDL_draw.h"

const int LENGTH = 450;

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  delete io;
  delete pter; 
  delete pterleft;
  delete SpriteFrameFactory::getInstance();
  delete gdata;
  delete view;

  
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
   drawTheStupidHud(false),
  io( IOManager::getInstance() ),
  clock( ),
  screen( io->getScreen() ),
  clouds( SpriteFrameFactory::getInstance()->getFrame("back", "back"), 2 ),
  hills( SpriteFrameFactory::getInstance()->getFrame("hill", "hill"), 1 ),
  ghostbcknd(SpriteFrameFactory::getInstance()->getFrame("ghostbcknd", "ghostbcknd"), 1 ),
  view(Viewport::getInstance()),
  pter( NULL ),
  pterleft(NULL),
 var1(0),
 var2(0),
 gui(),
 remainingTime(60),
 orbs()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  
  Vector2f position(gdata->getXmlInt("pterX"), gdata->getXmlInt("pterY"));
  Vector2f velocity(gdata->getXmlInt("pterXspeed"),
                    gdata->getXmlInt("pterYspeed"));
  pter = new MultiSprite(position, velocity, 
            MultiSpriteFrameFactory::getInstance()->getFrame("pter","pter"),
             "pter");


 pterleft= new MultiSprite(position, velocity, 
            MultiSpriteFrameFactory::getInstance()->getFrame("pterleft","pterleft"),
             "pterleft");

  orbs.pter = pter;
  orbs.pterLeft = pterleft;

  view->setObjectToTrack(pter);
 
 atexit(SDL_Quit);
 SDL_WM_SetCaption( "*** CpSc 870: Nikhil Bendre - Ghost Busters ***", NULL );
}

void Manager::update() {
  Uint32 ticks = clock.getElapsedTicks();
  orbs.update(ticks);
  if(var1==0){
  pter->update(ticks);
  }
  else{
  if(var1==1){
    if(var2==0){
   pterleft->X(pter->X());
   pterleft->Y(pter->Y());
  }
   var2=1;
  }
  pterleft->update(ticks);
}
  view->update();
  clouds.update();
  hills.update();
}


void Manager::drawHud() const {
  io->printMessageAt("**********************HELP******************", 150, 150);
  io->printMessageAt("Press <left> to move the Man to the left", 150, 190);
  io->printMessageAt("Press <right> to move the Man to the right", 150, 210);
  io->printMessageAt("Press <top> to move the Man to the top", 150, 230);
  io->printMessageAt("Press <bottom> to move the Man to the bottom", 150, 250);
  io->printMessageAt("Press <r> to shoot the ghost", 150, 270);
  io->printMessageAt("Press <F1> for help ", 150, 290);
  io->printMessageAt("***********************************************", 150, 310);
  SDL_Flip(screen);
}

void Manager::drawBackground() const {
  SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 190, 190, 190) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}


void Manager::draw() const {
  std::stringstream strm;
  std::string msg;
  clouds.draw();
  hills.draw();
  view->draw();
  int score = orbs.getScore(); 
  
	

if(var1==0)
  pter->draw();
 else
 pterleft->draw();
  orbs.draw();
  //strm << "Tracking orb number: " << orbs.getTrackedOrb()  << std::ends;
  //msg = strm.str();

  //io->printMessageAt("Press <space> to track the other orb", 10, 10);
  //io->printMessageAt(msg, 10, 30);
  strm << "Score is : " << score  << " Time is "<< remainingTime << std::ends;
  msg = strm.str();
  io->printMessageAt(msg, 10, 30);
  io->printMessageAt("Time: ", 10, 50);
  io->printMessageAt("Health: ", 10, 70);
if ( !drawTheStupidHud ){
  io->printMessageAt("Press F1 to see the options", 10, 10);
}
else if(drawTheStupidHud) drawHud();  
}

void Manager::play() {
  SDL_Event event;
  SDLSound sound;
  std::stringstream strm;
  std::string msg;
  
  bool showMenu = true;

  bool done = false;
  bool keyCatch = false;
  
  bool giveHelp = false;
  int shootflag=0;
  bool returnKey = false;
  
  int bar_length = LENGTH;
  unsigned totalTime = 60;
  unsigned ticks=100;
  unsigned timepau = 1000;
  int ff=0;

  ticks += clock.getElapsedTicks();
static_cast<MultiSprite*>(pter)->velocityX(0);
static_cast<MultiSprite*>(pter)->velocityY(0);

static_cast<MultiSprite*>(pterleft)->velocityX(0);
static_cast<MultiSprite*>(pterleft)->velocityY(0);

const Uint32 BLUE = SDL_MapRGB(screen->format, 0x00, 0x00, 0xcd);
const Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);

while ( not done ) {

    if(showMenu)
    {
         ghostbcknd.draw();
   	 gui.draw();
    	 SDL_Flip(screen);
	 
	
	 if(ff==0)
	 {
	 timepau = clock.getSeconds();
	 }


	 if(remainingTime==0)
	 {
		done = true;
	 }
	 SDL_PollEvent(&event);
    	 if (event.type ==  SDL_QUIT) { break; }
    	 if(event.type == SDL_KEYDOWN) 
	 {
      	switch ( event.key.keysym.sym ) {
        	case SDLK_ESCAPE : done = false; returnKey=false;  break;
        	case SDLK_q      : done = true; break;
		  
      	
		case SDLK_RETURN : {
        		  if ( !keyCatch ) {
            		  gui.lightOn();
           		  returnKey = true;
          		}
			
          	break;
         }
         case SDLK_DOWN   : {
          if ( !keyCatch ) {
            gui.increment();
          }
          break;
         }

	 case SDLK_UP   : {
          if ( !keyCatch ) {
            gui.decrement();
          }
          break;
         }

        default: break;
      } //end of switch
      keyCatch = true;
    } // end of keydown
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      if ( returnKey ) {
        //cout << "Chosen: " << gui.getIconClicked() << endl; 
	if(gui.getIconClicked()=="Help") 
	{
		done=true; 
	}

		
		
        SDL_Delay(1000);

	showMenu = false;
      }
      gui.lightOff();
      //break;
    } //end of keyUp


  }
  
  if(!showMenu) 
  {
		
	
	

	remainingTime = (totalTime+timepau) - clock.getSeconds();
	draw();
	Draw_FillRect(screen, 110, 60, bar_length, 10, WHITE);
	int getHealthBar = orbs.getBarLength();
	Draw_FillRect(screen, 110, 85, getHealthBar, 10, BLUE);
	
	SDL_Flip(screen);
	update();

	
	if(remainingTime==0 || getHealthBar <= 0)
	 {
		clock.isPaused();
						
		strm << "Final Score is : " << orbs.getScore() << std::ends;
		msg = strm.str();
 		io->printMessageAt(msg, 100, 200);
		done = true;
	 }
	
	
        static int tempv=60;
	if (not clock.isPaused() && remainingTime >= 0 && bar_length > 0) 
	 {
         if (tempv==(remainingTime+1)){
         tempv=remainingTime;
         //cout<<"enter here"<<bar_length<<endl;  
	 bar_length=bar_length-7;	
}         
	}
	SDL_Flip(screen);

	if ( clock.isPaused() ) clock.unpause();
	SDL_PollEvent(&event);
    	if (event.type ==  SDL_QUIT) { break; }
	if(event.type == SDL_KEYUP) 
	{ 
	     keyCatch = false; 
	     
	      if(var1==0) view->setObjectToTrack(pter);
	      else
	      view->setObjectToTrack(pterleft);
		
		keyCatch = false; 
		static_cast<MultiSprite*>(pter)->velocityX(0);
		static_cast<MultiSprite*>(pter)->velocityY(0);

		static_cast<MultiSprite*>(pterleft)->velocityX(0);
		static_cast<MultiSprite*>(pterleft)->velocityY(0);
	} //sdl-keyup
	
	    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : 
	{
	if(!keyCatch)
	{
		showMenu = true;
		if ( clock.isPaused() ) clock.unpause();
          	else clock.pause(); 
          	keyCatch = false; 
		ff=1;
	}
	keyCatch = true; 
	break;
	}
        case SDLK_q      : done = true; break;
	case SDLK_RETURN : {
          if ( !keyCatch ) {
          }
          break;
        }	

        case SDLK_SPACE      : {
          if (!keyCatch) {
            keyCatch = true;
            static int i = 0;
            i = (i + 1) % 2;
            if ( i ) orbs.setOrbToTrack(0);
            else view->setObjectToTrack(pter);
          }
          break;
        }
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
    
 case SDLK_0 : case SDLK_1 : case SDLK_2 : case SDLK_3 : 
        case SDLK_4 : case SDLK_5 : case SDLK_6 : case SDLK_7 : {
          if (!keyCatch) {
            keyCatch = true;
            io->clearString();
            io->buildString(event);
            int n = event.key.keysym.sym - SDLK_0;
            sound[n];
            break;
          }
       }



                        case SDLK_r : { 
                         if(shootflag==0)
                         	orbs.shoot(pter->X()+60,pter->Y()+20,0);
			  else
				orbs.shoot(pterleft->X()-60,pterleft->Y()+20,1);	
                           }
                          break;

                        case SDLK_LEFT  : { 

                        var1=1;
			shootflag=1;
                       view->setObjectToTrack(pterleft);
                        static_cast<MultiSprite*>(pterleft)->left();
			//cout<< " flag is "<<shootflag<<endl;

                           }
                          break;


                              case SDLK_RIGHT:
                              { 
                              view->setObjectToTrack(pter);
                              var1=0;
			      shootflag=0; 
                              if (var2==1){ pter->X(pterleft->X());
                              pter->Y(pterleft->Y());
                              var2=0;
                              }
                                static_cast<MultiSprite*>(pter)->right();
                                break;
                                 }

case SDLK_UP:  
if (var1==1)
{
view->setObjectToTrack(pterleft);
static_cast<MultiSprite*>(pterleft)->up();
break ;
}
static_cast<MultiSprite*>(pter)->up(); 
break;


case SDLK_DOWN:
if (var1==1){
view->setObjectToTrack(pterleft);
static_cast<MultiSprite*>(pterleft)->down();break;
}
static_cast<MultiSprite*>(pter)->down(); 
break;

 
case SDLK_F1:
{
	if(!keyCatch)
	{
		toggleTheStupidHud();
		giveHelp = true;
        
          	if ( clock.isPaused() ) clock.unpause();
          	else clock.pause(); 
          	keyCatch = false; 
        }     
        keyCatch = true; 
        break;
}
      
  
        default          : break;
	
	 

      }
    }



  }

  } //end while
}// finc
