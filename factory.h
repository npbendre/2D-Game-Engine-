#ifndef FACTORY__H
#define FACTORY__H

#include <string>
using std::string;
#include <map>
#include "frame.h"
#include "gamedata.h"

class AbstractFactory {
public:
  AbstractFactory() {}
  virtual ~AbstractFactory() {}

  virtual Frame* getFrame(const string& prefix, 
                          const string& framename) = 0;
private:
  static AbstractFactory* instance;
  AbstractFactory(const AbstractFactory&);
  AbstractFactory& operator=(const AbstractFactory&);
};
#endif
