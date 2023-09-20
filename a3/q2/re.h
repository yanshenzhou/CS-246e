 #ifndef RE_H
#define RE_H
#include <iostream>
#include <string>

namespace CS246E {


  /*
    RegExp: Our abstract virtual class from which all the regex components will inheirt.
      Note that Word has a different field from Concatenation, Disjunction and Star so we cant
      have a common field for the superclass. Each class needs to have a distructor and a matches function.
      So we can include that in our super class
  */

  class RegExp {
    public:

     virtual bool matches(const std::string s) = 0; // Make this a pure virtual function so it cant be called
     virtual ~RegExp() {}; // Empty destructor as there are no fields to delete

  };


  /*
    Disjunction: A regular expression in the form of {Left}|{Right}. Will contain a match if either the
       Left of the Right regex contains a match.
  */

  class Disjunction: public RegExp {
    RegExp *left; // Stores the left regex
    RegExp *right; // Stores the right regex
   public:
    Disjunction(RegExp *l, RegExp *r): left{l}, right{r} {}; //Sets the pointers to equal the adress of the pointers in the constructor

    bool matches (const std::string s) override {
      return (left->matches(s) || right->matches(s)); // Returns true if theres a match on the left regex or the right regex
    };

    ~Disjunction() override {
      delete left; // Deletes the left regex
      delete right; // Deletes the right regex
      left = nullptr; // Points away from freed memory on the left regex
      right = nullptr; // Points away from freed memory on the right regex
    }

  };


  /*
     Concatenation: A regular expression in the form of (Left)(Right) which returns a match if for any possible "cut"
       induuced in the string, the left regex has a match of the left side of the cut and the righ regex has a match for the
       right side of the cut.
     E.G: if the Regex is (aa)(bb) and we are given the string aabb, then a cut in between the second a and the first b would produce
       a string "aa" on the left, and "bb" on the right which would match their respective regexs.
  */
  class Concatenation: public RegExp {
    RegExp *left; // Stores the pointer to the left regex
    RegExp *right; // Store the pointer to the right regex
   public:
    Concatenation(RegExp *l, RegExp *r): left{l}, right{r} {}; // Points our fields to the address provided in the constructor

    bool matches (const std::string s) override { // Takes in a string
      for (size_t i = 0; i <= s.size(); i++) { // Loops through each index in the string
        if (left->matches(s.substr(0, i)) && right->matches(s.substr(i, s.size()-i))) { // Make a "cut" at that location, and checks if the left and right match
          return true;
        }
      }
      return false;
    };

    ~Concatenation() override {
      delete left; // Delete the left regex
      delete right; // Delete the right regex
      left = nullptr; // Point away from the freed memory
      right = nullptr; // Point away from the freed memory
    };

  };


  /*
     Star: A regular expression in the form of (center)* which will return match if the string can be split into n parts, and each of those
        parts match the center regex.
     E.G: Consider the regex (wa)* and consider the string wawawa. We can split the string into parts of size 2 to get "wa","wa","wa" which matches
        the inside regex.
  */

  class Star: public RegExp {
    RegExp *center; // Stores a single pointer to the center regex
   public:
    Star(RegExp *reg): center{reg} {}; // Sets the center pointer to the address provided in memory

    bool matches (const std::string s) override { // Takes in a string
      int size = s.size(); // Stores the size so we only acess it once
      if (size == 0) { return true; } // if the string is empty, star will always be a match
      if (center->matches(s)) { return true; } // For speed purposes check if the whole string is contained once

      int pos = 0; // Inital position
      for (int i = 1; i < size; ++i) { // Loop through the string
        if (center->matches(s.substr(pos,i))) { // If this section contains the math
           pos = pos + i; // Move our frame of reference forward
           i = 0;
        }

      }
      return (s.substr(pos,size).size() == 0); // If there is no left over then we are good!
    };

    ~Star() override {
      delete center; // Delete the center regex
      center = nullptr; // Set the pointer to look away from freed memory
    };

  };


  /*
     Word: A regular express in the form of (center) will return a match if and only if the string exactly matches, with no leftovers too.
  */

  class Word: public RegExp {
    std::string *center; // A string pointer to hold the value of word
   public:
    Word(const std::string &s): center{new std::string(s)} {}; // Makes a copy of the word and points towards it
    Word(std::string &&s): center{new std::string(s)} {}; // Moves the word into a string and makes a copy of it
    bool matches (const std::string s) override { // Takes in a string
      if (center->compare(s) == 0) { return true; } // If the string is a match return true
      return false;
    }

    ~Word() override {
      delete center; // Delete the string pointer
      center = nullptr; // Point away from freed memory
    };


  };
}
#endif

