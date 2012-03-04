#include "spriteFactory.h"
#include "ioManager.h"

SpriteFrameFactory* SpriteFrameFactory::getInstance() {
  if ( !instance ) instance = new SpriteFrameFactory;
  return instance;
}

SpriteFrameFactory::~SpriteFrameFactory() { 
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    SDL_Surface* surface = pos->second->getSurface();
    SDL_FreeSurface(surface);
    delete pos->second;
    ++pos;
  }
  frames.clear();
}

SpriteFrameFactory::SpriteFrameFactory() : 
  gdata( Gamedata::getInstance() ),
  frames( std::map<string, Frame*>() ) 
{}

Frame* SpriteFrameFactory::getFrame( const string& prefix,
                                     const string& framename) {
  // Frames are stored by filename, which is unique
  std::map<string, Frame*>::iterator pos = frames.find(framename); 
  if ( pos == frames.end() ) {
    const string filename = gdata->getXmlStr(framename+"File");
    bool colorKey = gdata->getXmlBool(prefix+"Transparency");
    SDL_Surface* surface = IOManager::
      getInstance()->loadAndSet(filename, colorKey);
  Frame* frame =
    new Frame(surface, 
      gdata->getXmlInt(prefix+"Width"), gdata->getXmlInt(prefix+"Height"),
      gdata->getXmlInt(prefix+"SrcX"), gdata->getXmlInt(prefix+"SrcY")); 
      frames[framename] = frame;
      return frame;
  }
  else return pos->second;
}

