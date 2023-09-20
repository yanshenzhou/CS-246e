#ifndef VIEW
#define VIEW

/*
  The default view, overrieden by ncurses view later
*/

class View {
   public:
     virtual void render() {};
     virtual void wins() {};
};
#endif
