#include <vector>
#include <map>
#include <string>
using std::string;
#include "ioManager.h"
#include "frame.h"
#include "parseXML.h"
#include "gamedata.h"

//change
#include "vector2f.h"

using std::vector;
using std::map;

class Gui {
public:
  Gui();
  void draw() const;
  const string& getIconClicked() const { return buttons[nextIcon].name; } 
  void increment() { nextIcon = (nextIcon + 1) % buttons.size(); }
  void decrement() { nextIcon = (nextIcon + buttons.size()-1) % buttons.size(); }
  void lightOn() { click = 1; }
  void lightOff() { click = 0; }
private:
  struct Button {
    Button(const string& n, const Frame& f, const Vector2f& pos) : 
      name(n), 
      frame(f),
      position(pos) 
    {}
    Button(const Button& button) : 
      name(button.name), 
      frame(button.frame),
      position(button.position) 
    {}
    string name;
    Frame frame; 
    Vector2f position;
  };
 //change
 // IOManager& io;
 IOManager* io;
 const Gamedata* gdata;
 // const ParseXML parser;
  // Buttons are stored in alphabetical order
  vector<Button> buttons; 
  vector<Frame> clicks;


  unsigned nextIcon;
  unsigned click;
};
