#include <iostream>
#include "vector.h"

using CS246E::vector;

struct Posn {
  int x, y;
  Posn(int x, int y): x{x}, y{y} {}
};

int main() {
  vector<int> v;
  v.push_back(1);
  v.push_back(10);
  v.push_back(100);
  v.at(0) = 2;

  vector<char> w;
  w.push_back('a');
  w.push_back('b');
  w.push_back('c');
  w.at(1) = 'z';

  vector<Posn> x;

  std::cout << v << std::endl;
  std::cout << w << std::endl;
}
