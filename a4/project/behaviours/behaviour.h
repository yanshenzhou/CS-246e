#ifndef BEH
#define BEH

class InteractableObject;
class GameRunner;

/*
  The Class for handeling updates to each object, each object can have multiple
    and in order for them to work properly, they need references to both the object
    and the game board itself.
*/
class Behaviour {
     int b_type;
     int x;
     int y;

     InteractableObject &obj;
     GameRunner &mod;

     int c_type;

     void tryMove(int x, int y);

   public:
     Behaviour(int b_type, int x, int y, InteractableObject &obj, GameRunner &mod, int c_type);
     void update();
};

#endif
