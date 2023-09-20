#include <iostream>
#include <fstream>
#include <string>

#include "re.h"

void processFile(std::istream &f, std::string reg, std::string filen) {
   auto re = CS246E::parseDisjunction(reg);
   std::string s;
   while (getline(f, s)){
      if (CS246E::containsMatch(re.get(), s) == true) { std::cout << filen  << s << std::endl; }
   }
}

int main(int argc, char *argv[]){

   int f_count = 0; // Count of all the files
   char* files[argc];
   std::string regex; // The pattern for the regular expression
   bool e_regex = true;


   for (int i = 1; i < argc; i++){
      if (e_regex){
         e_regex = false;
         regex = argv[i]; // Stores the first argument as the regex
      } else {
         files[f_count] = argv[i]; // Stores the filename in an array
         f_count++;
      }
   }

   if (f_count == 0){
      std::string filename = "";

      processFile(std::cin, regex, filename); //Read from std:::cin
   } else if (f_count == 1){
      std::ifstream f {files[0]};
      std::string filename = "";

      processFile(f, regex, filename); // read only one file in
   } else {
      for (int x = 0; x < f_count;  x++){
         std::ifstream f {files[x]};
         std::string filename = "";

         processFile(f, regex, filename); // Read each file in
      }
   }
   return (0);
}

