#include <iostream>
#include <fstream>
#include <string>

#include "filehelpers.h"


int main(int argc, char *argv[]){
   if (argc != 3){
      std::cerr << "Invalid number of args" << std::endl;
      return(1);
   }
   std::string suite = argv[1];
   std::string binary = argv[2];

   std::ifstream f {suite};

   f >> std::noskipws;
   char c;
   std::string line = "";

   while (f >> c){
      if (c == '\n' || c == ' '){
         if (!fileExists(line+".out")){
             std::cerr << "Cant find .out, missing/unreadable" << std::endl;
             return(1);
         }
         testFile(line, binary);
         line = "";
      } else {
         line.push_back(c);
      }
   }
   return (0);
}
