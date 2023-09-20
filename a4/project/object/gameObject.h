#ifndef GOBJ
#define GOBJ

#include <memory>
#include <vector>
#include <tuple>

#include "interactableObject.h"

/*
   This is a class allowing us to easily make game objects using 3 different constructors for the three required methods
*/

class GameObject: public InteractableObject {
   public:
     GameObject(int x, int y, int height, char r);
     GameObject(int x, int y, int w, int h, int height, char r);
     GameObject(std::vector<std::tuple<int, int, char>> vec, int h);
     //~GameObject();
};
#endif

