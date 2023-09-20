#ifndef MOD
#define MOD

#include "../view/view.h"
#include "../controller/controller.h"

#include <memory>

/*
   The abstract class for our game model, note that it has a reference to the controller and the view
      it has two different display methods 1) for normal running 2) for displaying a win, it also has a
      function for returning the most recent key press so behaviour can use it
*/
class Model {
     std::unique_ptr<View> view;
     std::unique_ptr<Controller> control;
   protected:
     void setView(std::unique_ptr<View> v);
     void setController(std::unique_ptr<Controller> c);
   public:
     virtual void play() = 0;
     void displayViews();
     void displayWin();
     int getKey();
};
#endif
