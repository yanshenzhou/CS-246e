#ifndef CVIEW
#define CVIEW
#include <iostream>
#include <ncurses.h>
#include <string>

#include "view.h"

class GameRunner;


/*
   The class for displaying input in ncurses mode, has a reference to the game runner and can show the normal game or win screen
*/
class CursesView: public View {
     GameRunner& game;
     WINDOW* win;

     void renderFrame();
     void renderObjects();
     void renderStatus();
   public:
     CursesView(GameRunner& game);
     void render() override;
     void wins() override;
     ~CursesView();

};
#endif
