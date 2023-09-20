#include "cursesControl.h"
#include <string>

CurseKeyboard::CurseKeyboard() {
  setlocale(LC_ALL, "");
}

int CurseKeyboard::action() {
  int n = getch();
  return n;
}
