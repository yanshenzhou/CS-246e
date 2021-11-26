#include "maze.h"
#include <string>
#include <iostream>
#include "writtenView.h"

using namespace std;

int main(int argc, char* argv[]){
  bool curses = true;
  bool walls = true;
  for ( int i = 1; i < argc; ++i ){
    std::string arg = argv[i];
    cout << arg << endl;
    if ( arg == "curses" ) curses = true;
    if ( arg == "walls" ) walls = true;
  }

  Maze m{15,15, curses, walls};
  m.play();
}
