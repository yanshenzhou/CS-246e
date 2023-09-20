#ifndef INTOB
#define INTOB

#include <memory>
#include <vector>
#include <tuple>

#include "../behaviours/behaviour.h"
#include "pixel.h"

class GameRunner;

/*
   A class that represents what it means to be a renderable object, it has a series of pixels and behaviours and can run the behaviours
      while also checking to see if it contains an x,y,h tuple used for interactions
*/
class InteractableObject {
     std::vector<std::unique_ptr<Pixel>> pixels;
     std::vector<std::unique_ptr<Behaviour>> behaviours;
   protected:
     void addPixel(int x, int y, int h, char r);
   public:
     int getX();
     int getY();
     int getH();

     void moveObject(int x_change, int y_change);

     bool contains(int x, int y, int h);

     void addBehaviour(int type, int x, int y, GameRunner &mod, int c);
     void runBehaviours();
     std::vector<std::tuple<int, int, int, char>> pixelData();
};
#endif
