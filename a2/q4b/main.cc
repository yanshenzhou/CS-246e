#include <iostream>
#include "map.h"
#include <map>

int main() {
 // std::cout << t.empty() << std::endl;
  //std::cout << t.size() << std::endl;
  //std::cout << t.at(1) << std::endl;
  //std::cout << t[1] << std::endl;
  //std::cout << t[0] << std::endl;
  //std::cout << t[2] << std::endl;
  cs246e::map<int, int> t;
  t[2];
  t.print();
  t[1];
  t.print();
  t[3];
  t.print();
  std::cout << "H" << std::endl;
  t.print();
  for (auto &v: t){
    std::cout << v.first << " " << v.second << std::endl;
  }
  t[0] = 2;
  t.print();
  t[1] = 5;
  t[2] = 10;
  t[5] = 72;
  std::cout << "B" << std::endl;
  t.print();
  std::cout << t.size() << std::endl;
  for (auto &v: t) {
    std::cout << v.first << " " << v.second << std::endl;
  }
  // t.erase(5);
  // for (auto &v: t) {
  //  std::cout << v.first << " " << v.second << std::endl;
  // }
  // std::cout << t.count(5) << std::endl;
  // t[5];
  // t.count(5);
  // std::cout << t.count(5) << std::endl;
  //t.clear();
  //for (auto &v: t){
  //   std::cout << v.first << " " << v.second << std::endl;
  //}

  //cs246e::map<int, int> y = {{1,2},{2,3},{4,5}};
  //t = y;
  //t["a"].print();

  //std::cout << "A" << std::endl;
  //for (auto &v: t) {
  //   std::cout << v.first << " " << v.second << std::endl;
  //}
 // t[0] = 99;
  //t.print();


}
