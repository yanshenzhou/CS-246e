#include <iostream>
#include <cstddef>
#include "list.h"

int main() {
  cs246e::list l;
  l.push_front(1).push_front(2).push_front(27);
  std::cout << l << std::endl;
  l[0] = 3;
  std::cout << l << std::endl;
  l.push_front(2);
  std::cout << l << std::endl;
  l.push_front(1);
  std::cout << l << std::endl;

  cs246e::list::iterator it = l.begin();

  std::cout << *l.insert(it,0) << std::endl;
  std::cout << l << std::endl;
  std::cout << *l.insert(++it, 55) << std::endl;
  std::cout << l << std::endl;
  std::cout << *l.insert(l.end(), 77) << std::endl;
  std::cout << l << std::endl;
}
