#include <iostream>
#include <fstream>
#include <string>

#include "process.h" 
int main(int argc, char *argv[]){
   bool fn = false, fi = false, fv = false;

   int f_count = 0;
   char* files[argc];
   std::string regex;
   bool e_regex = true;


   for (int i = 1; i < argc; i++){
      std::string arg = argv[i];
      if (arg.compare("-n") == 0){
      	fn = true; 
      }
      else if (arg.compare("-i") == 0){
      	fi = true;
      } 
      else if (arg.compare("-v") == 0){
        fv = true;
      } else {
      	if (e_regex){
           e_regex = false;
           regex = arg;
        } else {
           files[f_count] = argv[i];
           f_count++;
        }

      }
   }

   if (f_count == 0){
      std::string fname = "";

      return (!processFile(std::cin, regex, fname, fn, fi, fv));
   } else if (f_count == 1){
      std::ifstream f {files[0]};
      std::string fname = "";

      return(!processFile(f, regex, fname, fn, fi, fv));
   } else {
      bool linesfound = false;
      for (int x = 0; x < f_count;  x++){
         std::ifstream f {files[x]};
         std::string fname = files[x];
         fname.push_back(':');

         if (processFile(f, regex, fname, fn, fi, fv)){
             linesfound = true;
         }
      }
      return(!linesfound);
   }
   return (1);
}
