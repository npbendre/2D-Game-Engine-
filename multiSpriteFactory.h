#include "factory.h"

class MultiSpriteFrameFactory : public AbstractFactory {
public:
  static MultiSpriteFrameFactory* getInstance();
  ~MultiSpriteFrameFactory();

  Frame* getFrame(const string & prefix, const string& framename);
private:
  static MultiSpriteFrameFactory* instance;
  const Gamedata* gdata;
  std::map<string, Frame*> multiFrames;
  MultiSpriteFrameFactory();
  MultiSpriteFrameFactory(const MultiSpriteFrameFactory &);
  MultiSpriteFrameFactory& operator=(const MultiSpriteFrameFactory &);
};

