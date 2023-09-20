#include <iostream>
#include <string>

bool getnext(std::string word, int start);
bool compare(std::string letter, std::string eval, int* am, int pos, bool fi);
bool match(std::string input, std::string evalstring, bool fi);
bool processFile(std::istream &f, std::string regex, std::string filename, bool n, bool fi, bool v);
