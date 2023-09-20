#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

bool fileExists(std::string filename);
std::string getInput(std::string root);
bool runCommand(std::string command, std::string output, std::string input, std::string *exp, std::string act, int *xc);
bool testFile(std::string filestem, std::string binary);
