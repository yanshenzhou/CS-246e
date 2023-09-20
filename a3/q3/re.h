#ifndef RE_H
#define RE_H
#include <iostream>
#include <string>
#include <memory>
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
    std::unique_ptr<RegExp> left; // Stores a unique ptr the left regex
    std::unique_ptr<RegExp> right; // Stores a unique ptr to the right regex
   public:
    Disjunction(std::unique_ptr<RegExp> l, std::unique_ptr<RegExp> r): left{std::move(l)}, right{std::move(r)} {}; // Moves the unique ptrs provided into our fields

    bool matches (const std::string s) override {
      return (left->matches(s) || right->matches(s)); // Returns true if theres a match on the left regex or the right regex
    };

    ~Disjunction() override {
       // No need to destroy field, as they are all unique_ptrs and will auto delete
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
    std::unique_ptr<RegExp> left; // Stores the unique pointer to the left regex
    std::unique_ptr<RegExp> right; // Store the unique pointer to the right regex
   public:
    Concatenation(std::unique_ptr<RegExp> l, std::unique_ptr<RegExp> r): left{std::move(l)}, right{std::move(r)} {}; // Moves the unique ptrs provided into our fields

    bool matches (const std::string s) override { // Takes in a string
      for (size_t i = 0; i <= s.size(); i++) { // Loops through each index in the string
        if (left->matches(s.substr(0, i)) && right->matches(s.substr(i, s.size()-i))) { // Make a "cut" at that location, and checks if the left and right match
          return true;
        }
      }
      return false;
    };

    ~Concatenation() override {
       // No need to destory fields as they are all unique ptrs
    };

  };


  /*
     Star: A regular expression in the form of (center)* which will return match if the string can be split into n parts, and each of those
        parts match the center regex.
     E.G: Consider the regex (wa)* and consider the string wawawa. We can split the string into parts of size 2 to get "wa","wa","wa" which matches
        the inside regex.
  */

  class Star: public RegExp {
    std::unique_ptr<RegExp> center; // Stores a single unique pointer to the center regex
   public:
    Star(std::unique_ptr<RegExp> reg): center{std::move(reg)} {}; // Moves the contents of the provided unqiue ptr into our field

    bool matches (const std::string s) override { // Takes in a string
      int size = s.size(); // Stores the size so we only acess it once
      if (size == 0) { return true; } // if the string is empty, star will always be a match
      if (center->matches(s)) { return true; } // If the whole string is contained, skip and return true

      int pos = 0; // Intal postion of a part
      for (int i = 1; i < size; ++i) {
         if (center->matches(s.substr(pos,i))) { // If theres a part that matches make a cut
            pos = pos + i; // Increase pos to account for the matching part
            i = 0;
         }
      }
      return (s.substr(pos,size).size() == 0); // If there is a part not accounted for, * does not work
    };

    ~Star() override {
      // No need to delete a unique ptr
    };

  };


  /*
     Word: A regular express in the form of (center) will return a match if and only if the string exactly matches, with no leftovers too.
  */

  class Word: public RegExp {
    std::unique_ptr<std::string> center; // A string unique pointer to hold the value of word
   public:
    Word(const std::string &s): center{std::move(new std::string(s))} {}; // Moves the word and points towards it
    Word(std::string &&s): center{std::move(new std::string(s))} {}; // Moves the word into a string and makes a moves of it
    bool matches (const std::string s) override { // Takes in a string
      if (center->compare(s) == 0) { return true; } // If the string is a match return true
      return false;
    }

    ~Word() override {
      // No need to delete a unique ptr
    };


  };
}
#endif

