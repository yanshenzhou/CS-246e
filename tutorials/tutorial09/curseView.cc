#include "curseView.h"
#include <ncurses.h>
#include "maze.h"

Curses::Curses(int rows, int cols, Maze& m): width{rows}, height{cols}, model{m}{
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  displayMap[EMPTY] = ' ';
  displayMap[WALL] = '#';
  displayMap[GOAL] = '*';
  displayMap[PLAYER] = '&';
  
  // exterior walls
  for (int i = 0; i < cols + 2; ++i){
    mvwaddch(stdscr, 0, i, ACS_HLINE);
    mvwaddch(stdscr, rows+1, i, ACS_HLINE);
  }
  for (int i = 0; i < rows + 2; ++i){
    mvwaddch(stdscr, i, 0, ACS_VLINE);
    mvwaddch(stdscr, i, cols+1, ACS_VLINE);
  }
  mvwaddch(stdscr, 0, 0, ACS_ULCORNER);
  mvwaddch(stdscr, 0, cols+1, ACS_URCORNER);
  mvwaddch(stdscr, rows+1, 0, ACS_LLCORNER);
  mvwaddch(stdscr, rows+1, cols+1, ACS_LRCORNER);

  // fill in map
  for (int i = 0; i < rows; ++i ){
    for( int j = 0; j < cols; ++j ){
      mvwaddch(stdscr, i+1, j+1, displayMap[EMPTY]);
    }
  }
}

void Curses::updateWalls(){

  // fix inner walls
  for ( int i = 0; i < height; ++i ){
    for ( int j = 0; j < width; ++j ){
      if ( model.getState(i, j) != WALL ) continue;
      bool up = false, right = false, down = false, left = false;
      if ( i == 0 || model.getState(i-1,j) == WALL ) up = true; 
      if ( j > width - 1  || model.getState(i,j+1) == WALL ) right = true; 
      if ( i > height - 1 || model.getState(i+1,j) == WALL ) down = true; 
      if ( j == 0 || model.getState(i,j-1) == WALL ) left = true; 
      if (  up &&  right &&  down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_PLUS);
      if (  up &&  right &&  down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_LTEE);
      if (  up &&  right && !down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_BTEE);
      if (  up &&  right && !down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_LLCORNER);
      if (  up && !right &&  down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_RTEE);
      if (  up && !right &&  down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_VLINE);
      if (  up && !right && !down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_LRCORNER);
      if (  up && !right && !down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_VLINE);
      if ( !up &&  right &&  down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_TTEE);
      if ( !up &&  right &&  down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_ULCORNER);
      if ( !up &&  right && !down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_HLINE);
      if ( !up &&  right && !down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_HLINE);
      if ( !up && !right &&  down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_URCORNER);
      if ( !up && !right &&  down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_VLINE);
      if ( !up && !right && !down &&  left ) mvwaddch(stdscr,i+1,j+1,ACS_HLINE);
      if ( !up && !right && !down && !left ) mvwaddch(stdscr,i+1,j+1,ACS_PLUS); // this should never happen
    }
  }

  // fix outer walls
  for ( int i = 0; i < width; ++i ){
    if ( model.getState(0,i) == WALL ) mvwaddch(stdscr,0,i+1,ACS_TTEE);
    if ( model.getState(height-1,i) == WALL ) mvwaddch(stdscr,height+1,i+1,ACS_BTEE);
  }
  for ( int i = 0; i < height; ++i ){
    if ( model.getState(i,0) == WALL ) mvwaddch(stdscr,i+1,0,ACS_LTEE);
    if ( model.getState(i,width-1) == WALL ) mvwaddch(stdscr,i+1,width+1,ACS_RTEE);
  }
}

void Curses::displayView(){
  if ( firstDisplay ){
    firstDisplay = false;
    updateWalls();
  }
  refresh();
}

void Curses::update(const std::string& msg){
  wmove(stdscr, height+3,0);
  waddstr(stdscr,"                                              ");
  wmove(stdscr, height+3,0);
  waddstr(stdscr,msg.c_str());
}


void Curses::update(int row, int col, State state){
  mvwaddch(stdscr,row+1,col+1,displayMap[state]);
}

Curses::~Curses(){ endwin(); }
