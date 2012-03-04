#include "drawable.h"
#include "frame.h"
#include "ioManager.h"
#include "viewport.h"

Frame::Frame( ) 
  : screen(NULL), spriteSurface(NULL), 
    spriteWidth(0), spriteHeight(0),
    spriteSourceX(0), spriteSourceY(0)
{ }



Frame::Frame( const Frame& frame ) :
  screen(frame.screen),
  spriteSurface(frame.spriteSurface), 
  spriteWidth(frame.spriteWidth), spriteHeight(frame.spriteHeight),
  spriteSourceX(frame.spriteSourceX), spriteSourceY(frame.spriteSourceY) 
  { }

Frame::Frame( SDL_Surface* spr, Uint16 sprite_width, Uint16 sprite_height,
              Sint16 src_x, Sint16 src_y) :
  screen(IOManager::getInstance()->getScreen()),
  spriteSurface(spr), 
  spriteWidth(sprite_width), spriteHeight(sprite_height),
  spriteSourceX(src_x), spriteSourceY(src_y) {
}

/*
Frame::~Frame()
{
SDL_FreeSurface(screen);
SDL_FreeSurface(spriteSurface);
}
*/


Frame& Frame::operator=(const Frame& rhs) {
  spriteSurface = rhs.spriteSurface;
  screen = rhs.screen;
  spriteWidth = rhs.spriteWidth;
  spriteHeight = rhs.spriteHeight;
  spriteSourceX = rhs.spriteSourceX;
  spriteSourceY = rhs.spriteSourceY;
  return *this;
}

void Frame::draw(const Vector2f& position) const {
  Sint16 x = Viewport::getInstance()->X()+100;
  Sint16 y = position[1];
  draw(x, y);
}

void Frame::draw(Sint16 x, Sint16 y) const {
  SDL_Rect src = { spriteSourceX, spriteSourceY, 
                   spriteWidth, spriteHeight 
                 };    
  x -= Viewport::getInstance()->X();
  y -= Viewport::getInstance()->Y();
  SDL_Rect dest = {x, y, spriteWidth, spriteHeight };
  SDL_BlitSurface(spriteSurface, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  SDL_Rect src = { sx, sy, spriteWidth, spriteHeight };    
  SDL_Rect dest = {dx, dy, spriteWidth, spriteHeight };
  SDL_BlitSurface(spriteSurface, &src, screen, &dest);
}


