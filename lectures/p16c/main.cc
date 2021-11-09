#include <iostream>
#include <utility>
#include "vector.h"

using CS246E::vector;

struct Posn {
  int x, y;
  Posn(int x, int y): x{x}, y{y} {
    std::cout << "Posn ctor:  x = " << x << ", y = " << y << std::endl;
  }
  Posn(const Posn &p): x{p.x}, y{p.y} {
    std::cout << "Posn copy ctor:  x = " << x << ", y = " << y << std::endl;
  }
  Posn(Posn &&p) noexcept: x{p.x}, y{p.y} {
    std::cout << "Posn move ctor:  x = " << x << ", y = " << y << std::endl;
  }
  ~Posn() {
    std::cout << "Posn dtor:  x = " << x << ", y = " << y << std::endl;
  }
};

std::ostream &operator<<(std::ostream &out, const Posn &p) {
  return out << '(' << p.x << ',' << p.y << ')';
}

int main() {
  vector<int> v;
  v.push_back(1);
  v.push_back(10);
  v.push_back(100);
  v.at(0) = 2;

  vector<int> w(10);

  std::cout << v << std::endl;
  std::cout << w << std::endl;

  vector<int> x(10, 5);
  std::cout << x << std::endl;

  vector<int> y {2,3,5,7,11};
  std::cout << y << std::endl;

  vector<Posn> vp {{1, 2}, {3, 4}};
  vp.emplace_back(5, 6);
  std::cout << vp << std::endl;
}
