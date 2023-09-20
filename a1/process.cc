#include <iostream>
#include <fstream>
#include "process.h"


int* getcount(std::istream &f){
   f >> std::noskipws;

   char c, p = ' ';

   static int retVal[3] = {0,0,0};
   while (f >> c){
      retVal[2] = retVal[2] + 1;
      if (c == '\n'){
        retVal[0] = retVal[0] + 1;
      }
      if ((c == '\n' || c == ' ') && ((p != ' ') && (p != '\n'))){
        retVal[1] = retVal[1] + 1;
      }
      p = c;
   }
   return retVal;
}

