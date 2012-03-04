#include "multiSpriteFactory.h"
#include "ioManager.h"

MultiSpriteFrameFactory* MultiSpriteFrameFactory::getInstance() {
  if ( !instance ) instance = new MultiSpriteFrameFactory;
  return instance;
}

MultiSpriteFrameFactory::~MultiSpriteFrameFactory() { 
  std::map<string, Frame*>::iterator pos = multiFrames.begin(); 
  while ( pos != multiFrames.end() ) {
    SDL_Surface* surface = pos->second->getSurface();
    SDL_FreeSurface(surface);

    // Note that the order of deletion matters. For example, I can't
    // delete frames before I delete each individual frame.
    const string framename = pos->first;
    unsigned numberOfFrames = gdata->getXmlInt(framename+"Frames");
    Frame *frames = pos->second;
    for (unsigned i = 0; i < numberOfFrames; ++i) {
      frames[i].~Frame();
    }
    operator delete(frames);
    ++pos;
  }
  multiFrames.clear();
}

MultiSpriteFrameFactory::MultiSpriteFrameFactory() : 
  gdata( Gamedata::getInstance() ),
  multiFrames( std::map<string, Frame*>() ) 
{}

Frame* MultiSpriteFrameFactory::getFrame(const string& prefix,
                                         const string& framename) {
  std::map<string, Frame*>::iterator pos = multiFrames.find(framename); 
  if ( pos == multiFrames.end() ) {
    const string filename = gdata->getXmlStr(framename+"File");
    bool colorKey = gdata->getXmlBool(prefix+"Transparency");
    SDL_Surface* surface = IOManager::
      getInstance()->loadAndSet(filename, colorKey);
  
    unsigned numberOfFrames = gdata->getXmlInt(prefix+"Frames");
    Uint16 pwidth = gdata->getXmlInt(prefix+"Width") / numberOfFrames;
    Uint16 pheight = gdata->getXmlInt(prefix+"Height");
    Uint16 srcX = gdata->getXmlInt(prefix+"SrcX");
    Uint16 srcY = gdata->getXmlInt(prefix+"SrcY");
    // I need to use "operator new" and then "placement new" to
    // avoid calls to the default constructor.
    void *rawMemory = operator new[](numberOfFrames*sizeof(Frame));
    Frame* frames = static_cast<Frame*>(rawMemory);
    // construct the Frame objects in memory using
    // "placement new" (see Scott Myeres, Item 8)
    for (unsigned i = 0; i < numberOfFrames; ++i) {
      unsigned frameX = i * pwidth + srcX;
      new (&frames[i]) Frame( surface, pwidth, pheight, frameX, srcY);
    }
    multiFrames[framename] = frames;
    return frames;
  }
  else return pos->second;
}

