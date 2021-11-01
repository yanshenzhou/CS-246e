#include <iostream>
#include <string>
#include "re.h"
using namespace std;

bool containsMatch(CS246E::RegExp *re, const string &s) {
  string s2 = '\200' + s + '\201';
  // then proceed using s2
  return false;
}

int main() {
  string s;
  while (getline(cin, s)) {
    auto re = CS246E::parseDisjunction(s);
    cout << *re << endl;
    while (getline(cin, s)) {
      if (s == "q") break;
      cout << boolalpha << containsMatch(re.get(), s) << endl;
    }
  }
}
