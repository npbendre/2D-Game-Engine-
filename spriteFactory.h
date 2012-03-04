#include "factory.h"

class SpriteFrameFactory : public AbstractFactory {
public:
  static SpriteFrameFactory* getInstance();
  ~SpriteFrameFactory();

  Frame* getFrame(const string & name);
  Frame* getFrame(const string & tagPrefix, const string& framename);
private:
  static SpriteFrameFactory* instance;
  const Gamedata* gdata;
  std::map<string, Frame*> frames;
  SpriteFrameFactory();
  SpriteFrameFactory(const SpriteFrameFactory &);
  SpriteFrameFactory& operator=(const SpriteFrameFactory &);
};

