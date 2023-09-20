#include <string>
#include <tuple>

#include "cursesView.h"
#include "../model/gameRunner.h"

CursesView::CursesView(GameRunner& game): game{game}, win{nullptr} {
   initscr();
   cbreak();
   noecho();
   intrflush(stdscr, TRUE);

   nodelay(stdscr, TRUE);
   scrollok(stdscr, TRUE);

   win = newwin(25,80,5,5);
   refresh();
   box(win, 0, 0);
}

void CursesView::renderObjects() {
   for (auto &elem : game.getObjects()) {
      if (std::get<1>(elem) <= 21 && std::get<0>(elem) <= 79) {
         mvwaddch(win, std::get<1>(elem), std::get<0>(elem), std::get<3>(elem));
      }
   }
}

void CursesView::renderStatus() {
   int curr_row = 22;
   for (auto &str : game.getStatus()) {
      mvwaddstr(win, curr_row, 0, str.c_str());
      curr_row++;

   }

}

void CursesView::render() {
   werase(win);
   renderObjects();
   renderStatus();
   wrefresh(win);
   move(0,0);
}

void CursesView::wins() {
   werase(win);
   mvwaddstr(win, 10, 20, "YOU WIN!!!!");
   wrefresh(win);
   move(0,0);
}

CursesView::~CursesView() {
   delwin(win);
   endwin();
}
