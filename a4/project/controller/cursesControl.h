#ifndef CURSEKEY
#define CURSEKEY

#include <iostream>
#include <ncurses.h>

#include "controller.h"

/*
   The concrete class used for quering input while the ncurses window is running
*/
class CurseKeyboard: public Controller {
   int action() override;
  public:
   CurseKeyboard();
};

#endif
