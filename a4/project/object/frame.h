#ifndef FRAME
#define FRAME

#include "interactableObject.h"

/*
   A class for easility making frames, we have two types so it will construct them differently
*/

class Frame: public InteractableObject {
   public:
     Frame(int type);
};
#endif
