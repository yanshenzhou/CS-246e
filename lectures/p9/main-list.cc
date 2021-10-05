#include <iostream>
#include <cstddef>
#include "list.h"

int main() {
  CS246E::list l;
  l.push_front(3).push_front(2).push_front(1);
  const CS246E::list l2 = l;

  l[1] = 4;
  // l2[1] = 5;
  std::cout << l << std::endl;
  std::cout << l2 << std::endl;
}
