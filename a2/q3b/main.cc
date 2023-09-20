#include <iostream>
#include "deque.h"
using cs246e::deque;

int main() {

  deque<int> d {1,2,3,4,5,6,7,8,10,12,14,15};
  deque<int> b;
  b = d;

  std::cout << "LOOP BASED TESTS" << std::endl;
  std::cout << b.at(2) << std::endl;
  b[2] = 999;
  std::cout << d.at(2) << std::endl;
  std::cout << "5-6" << std::endl;

  for (deque<int>::iterator x = d.begin(); x != d.end(); ++x) {
     std::cout << *x << std::endl;
  }

  d.push_back(7);
  d.push_back(8);
  d.push_back(9);

  for (int i = 10; i <= 120; i++){
     d.push_back(i);
  }
  for (int i = 5; i < 20; i++){
     d.pop_back();
     d.pop_front();
  }
  deque<int> c = d;

  for (deque<int>::iterator x = c.begin(); x != c.end(); ++x) {
      std::cout << *x << std::endl;
   }

}
