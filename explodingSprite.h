#include <vector>
#include <iostream>
using std::vector;

#include "explosion.h"

class ExplodingSprite : public Sprite {
public:
  ExplodingSprite(const Sprite&, int);
  ~ExplodingSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void makeChunks(unsigned int);
  void makePerfectChunks(unsigned int);
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  SDL_Surface *screen;
  const Frame *frame;
  SDL_Surface *spriteSurface;
  std::vector<Explosion> chunks;
  std::vector<Explosion> freeList;

  Vector2f getNewVelocity() const;
  ExplodingSprite(const ExplodingSprite&);
  ExplodingSprite& operator=(const ExplodingSprite&);
};
