#include "gui.h"
#include "viewport.h"

Gui::Gui() : 
  io( IOManager::getInstance() ),
   gdata( Gamedata::getInstance() ),
//  parser( "xmlSpec/menu.xml" ),
  buttons(), 
  clicks(),
  nextIcon(0),
  click(0) 
{
  float x = gdata->getXmlInt("newX");
  float y = gdata->getXmlInt("newY");

  string filename = gdata->getXmlStr("newFile");
  SDL_Surface* surfaceNew(io->loadAndSet(filename, true));
  Frame newFrame(surfaceNew, 
            gdata->getXmlInt("newWidth"), 
            gdata->getXmlInt("newHeight"), 
            gdata->getXmlInt("pterSrcX"), 
            gdata->getXmlInt("pterSrcX")); 
  buttons.push_back( Button("New", newFrame, Vector2f(x, y)) );

  x = gdata->getXmlInt("openX");
  y = gdata->getXmlInt("openY");
  filename = gdata->getXmlStr("openFile");
  SDL_Surface* surfaceOpen(io->loadAndSet(filename, true));
  Frame openFrame(surfaceOpen, 
            gdata->getXmlInt("openWidth"), 
            gdata->getXmlInt("openHeight"), 
            gdata->getXmlInt("openSrcX"), 
            gdata->getXmlInt("openSrcY")); 
  //buttons.push_back( Button("Open", openFrame, Vector2f(x, y)) );
 
 
  
  x = gdata->getXmlInt("helpX"); 
  y = gdata->getXmlInt("helpY"); 
  filename = gdata->getXmlStr("helpFile");
  SDL_Surface* surfaceHelp(io->loadAndSet(filename, true));
  Frame helpFrame(surfaceHelp, 
            gdata->getXmlInt("helpWidth"), 
            gdata->getXmlInt("helpHeight"), 
            gdata->getXmlInt("helpSrcX"), 
            gdata->getXmlInt("helpSrcY")); 
  buttons.push_back( Button("Help", helpFrame, Vector2f(x, y)) );

  filename = gdata->getXmlStr("clickoffFile");
  SDL_Surface* surfaceOff(io->loadAndSet(filename, true));
  Frame clickoff(surfaceOff, 
              gdata->getXmlInt("clickoffWidth"), 
              gdata->getXmlInt("clickoffHeight"), 
              gdata->getXmlInt("clickoffSrcX"), 
              gdata->getXmlInt("clickoffSrcX")); 
  clicks.push_back( clickoff );

  filename = gdata->getXmlStr("clickonFile");
  SDL_Surface* surfaceOn(io->loadAndSet(filename, true));
  Frame clickon(surfaceOn, 
              gdata->getXmlInt("clickonWidth"), 
              gdata->getXmlInt("clickonHeight"), 
              gdata->getXmlInt("clickonSrcX"), 
              gdata->getXmlInt("clickonSrcX")); 
  clicks.push_back( clickon );
}

void Gui::draw() const {
  buttons[0].frame.draw( buttons[0].position );
  //buttons[1].frame.draw( buttons[1].position );
  //buttons[2].frame.draw( buttons[2].position );
  buttons[1].frame.draw( buttons[1].position );
  Vector2f pos = buttons[nextIcon].position;
  clicks[click].draw(Viewport::getInstance()->X()+50, pos[1]+20);
}

