#include <iostream>
#include <fstream>
#include <string>

#include "process.h"














void output(int lines, int words, int chars, const char* file,
            bool a, bool b, bool c){
   if (a){
      std::cout << " " << lines;
   }
   if (b){
      std::cout << " " << words;
   }
   if (c){
      std::cout << " " << chars;
   }
   std::string sfile = file;
   if (sfile.compare("ign") != 0){
      std::cout << " " << file;
   }
   std::cout << std::endl;
}
 
int main(int argc, char *argv[]){
   bool a = false, b = false, c = false;

   int f_count = 0;
   char* files[argc];

   for (int i = 0; i < argc; i++){
      std::string arg = argv[i];
      if (arg.compare("-l") == 0){
         a = true;
      }
      else if (arg.compare("-w") == 0){
         b = true;
      }
      else if (arg.compare("-c") == 0){
         c = true;
      }
      else {
         files[f_count] = argv[i];
         f_count++;
      }
   }

   if (!a && !b && !c){
      a = true;
      b = true;
      c = true;
   }
   if (f_count == 1) {
      int* cnt;

      cnt = getcount(std::cin);

      output(cnt[0], cnt[1], cnt[2], "ign", a, b, c);
   }
   else if (f_count == 2){
      int* cnt;
      std::ifstream f {files[1]};

      cnt = getcount(f);

      output(cnt[0], cnt[1], cnt[2], files[1], a, b, c);
   } else {
      int l_ct = 0, w_ct = 0, c_ct = 0;
      for (int x = 1; x < f_count; x++){
         int* cnt;
         std::ifstream f {files[x]};

         cnt = getcount(f);

         output(cnt[0], cnt[1], cnt[2], files[x], a, b, c);

         l_ct += cnt[0];
         w_ct += cnt[1];
         c_ct += cnt[2];

         cnt[0] = 0;
         cnt[1] = 0;
         cnt[2] = 0;
      }

      output(l_ct, w_ct, c_ct, "total", a, b, c);

   }

}
