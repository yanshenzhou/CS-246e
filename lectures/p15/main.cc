#include <iostream>
#include "unique_ptr.h"

struct Posn {
  int x, y;
  Posn(int x, int y): x{x}, y{y} {
    std::cout << "Posn ctor:  x = " << x << ", y = " << y << "\n";
  }
  ~Posn() {
    std::cout << "Posn dtor:  x = " << x << ", y = " << y << "\n";
  }
};

struct Posn2: public Posn {
  Posn2(int x, int y): Posn{x, y} {}
};

int main() {
  {
    Posn p{1, 2};
  }
  {
    Posn *q = new Posn {3, 4};  // This will leak
  }
  {
    CS246E::unique_ptr<Posn> r {new Posn {5, 6}};
  }
  auto s = CS246E::make_unique<Posn>(7, 8);
  CS246E::unique_ptr<Posn> pp {new Posn2{9, 10}};
}
