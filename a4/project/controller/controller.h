#ifndef CONT
#define CONT

#include <string>

/*
   The class used for getting input from the keybaord, the action is queried using getAction(). Note that this is the abstract class
*/
class Controller {
   virtual int action() = 0;
  public:
   int getAction();
   virtual ~Controller() = default;
};

#endif
