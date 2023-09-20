#include <iostream>
#include <fstream>
#include <string>

#include "process.h"

std::string getcurrenteval(std::string word, int start){
   int subsize = 0;
   int wlength = word.size();

   bool existline = false;

   for (int i = 0; i < wlength; i++){
      if (word.at(i) == '|'){
         existline = true;
      }
   }

   if (existline){
      return word;
   }

   if ((start + 1 < wlength) &&
       ((word.at(start + 1) == '*') ||
        (word.at(start + 1) == '+') ||
        (word.at(start + 1) == '?'))) {

      subsize = 2;

   } else if (word.at(start) == '[') {
       char p = word.at(start);
       while (p != ']'){
          p = word.at(start + subsize);
          subsize = subsize + 1;
       }
   } else if (word.at(start) == '\\'){

       subsize = 2;
   } else {

      subsize = 1;

   }

   return word.substr(start, subsize);

}


bool compare(std::string letter, std::string eval, int* am, int pos, bool fi){

   if (eval.size() == 1){
      if (eval.at(0) == '.' || !fi && (eval.at(0) == letter.at(0)) ||
          (fi && (eval.at(0) == letter.at(0) ||
                  eval.at(0) == letter.at(0) + 'a' - 'A' ||
                  eval.at(0) == letter.at(0) + 'A' - 'a'))){
         *am = 0;
         return(true);
      } else if (eval.at(0) == '$') {
         return(false);
      } else if (eval.at(0) == '^') {
         if (pos == 0) {
            *am = -1;
            return(true);
         }
      }

   } else if (eval.size() >= 2) {
      if (eval.at(0) == '['){
         int disp = 0;
         if (eval.at(1) == '^'){
            disp = 1;
         }
         std::string query = eval.substr(1 + disp, eval.size() -2 -disp);

         bool inrange = false;
         for (int i = 0; i < query.size(); i++){
            if (query.at(i) == letter.at(0)){
               inrange = true;
            }

         }
         *am = 0;
         return ((inrange + disp)%2);
      } else if (eval.at(0) == '\\') {

         *am = 0;

         if (letter.at(0) == eval.at(1)){
             return true;
         }
         return false;

      } else if (eval.at(1) == '*' || eval.at(1) == '?' || eval.at(1) == '+'){
         *am = 0;
         char currlett = letter.at(*am);

         while (*am < letter.size() && currlett == eval.at(0)){
            *am = *am +1;
            if (*am < letter.size()){
                currlett = letter.at(*am);
            }
         }

         if (eval.at(1) == '?'){
            if (*am == 0){
               *am = -1;
               return true;
            }
            *am = 0;
            return true;
         } else if (eval.at(1) == '+') {
            if (*am == 0){
               return false;
            }
            *am = *am -1;
            return true;
         }
         *am = *am -1;
         return true;
      } else {
         for (int i = 0; i < eval.size(); i++){
            if (eval.at(i) == '|'){
                std::string q1 = eval.substr(0, i);
                std::string q2 = eval.substr(i+1, eval.size() - i -1);

                if (match(letter, q1, fi) || match(letter, q2, fi)){
                   return true;
                }
                return false;
            }
         }
      }

   }
   return (false);
}


bool match(std::string input, std::string evalstring, bool fi){

   int strlen = input.size();
   int evalpos = 0;
   std::string letter;
   std::string evalslice;

   bool wordmatch = false;

   if (evalstring.size() == 0){
      return (true);
   }
   for (int i = 0; i < strlen; i++){
      letter = input.substr(i, input.size());
      evalslice = getcurrenteval(evalstring, evalpos);

      int es = 0;
      wordmatch = compare(letter, evalslice, &es, i, fi);

      if (wordmatch){
         evalpos = evalpos + evalslice.size();
         i = i + es;
      } else {
         if (evalpos != 0){
            i = i -1;
         }
         evalpos = 0;
      }

      if (evalpos == evalstring.size()){
         return (true);
      }
   }

   evalslice = getcurrenteval(evalstring, evalpos);

   if (evalslice.at(0) == '$' && evalslice.size() == 1){
      return (true);
   }
   return (false);
}


bool processFile(std::istream &f, std::string regex, std::string filename, bool n, bool fi, bool v){
   f >> std::noskipws;

   char c = ' ';
   std::string currline;
   bool lmatch = false;
   bool retVal = false;
   int lcount = 0;

   while (f >> c){
      if (c == '\n'){
        lcount = lcount + 1;
        lmatch = match(currline, regex, fi);

        if ((lmatch + v) % 2 == 1){
           retVal = true;
           std::cout << filename;
           if (n){
              std::cout << lcount << ":";
           }
           std::cout << currline << std::endl;
        }
        currline = "";
      }else{
        currline.push_back(c);
      }
   }
   return retVal;
}

