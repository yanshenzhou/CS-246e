#ifndef RE_H
#define RE_H
#include <iostream>
#include <string>
#include <memory>

namespace CS246E {


  class RegExp {
    public:

     virtual bool matches(std::string s) = 0;
     virtual ~RegExp() {};

  };

  class Disjunction: public RegExp {
    std::unique_ptr<RegExp> left;
    std::unique_ptr<RegExp> right;
   public:
    Disjunction(std::unique_ptr<RegExp> l, std::unique_ptr<RegExp> r): left{std::move(l)}, right{std::move(r)} {};

    bool matches (const std::string s) override {
      return (left->matches(s) || right->matches(s));
    };

    ~Disjunction() override {
      // Nothing
    }

  };


  class Concatenation: public RegExp {
    std::unique_ptr<RegExp> left;
    std::unique_ptr<RegExp> right;
   public:
    Concatenation(std::unique_ptr<RegExp> l, std::unique_ptr<RegExp> r): left{std::move(l)}, right{std::move(r)} {};

    bool matches (const std::string s) override {
      for (size_t i = 0; i <= s.size(); i++) {
        if (left->matches(s.substr(0, i)) && right->matches(s.substr(i, s.size()-i))) {
          return true;
        }
      }
      return false;
    };

    ~Concatenation() override {
      // Nothing
    };

  };

  class Star: public RegExp {
    std::unique_ptr<RegExp> center;

   public:
    Star(std::unique_ptr<RegExp> reg): center{std::move(reg)} {};

    bool matches (const std::string s) override {
      int size = s.size();
      if (size == 0) { return true; }
      for (int i = 1; i <= size; ++i) {
        if (size % i == 0) {
          bool match = true;
          for (int x = 0; x < size; x += i) {
            if (center->matches(s.substr(x,i)) == false) {
              match = false;
            }
          }
          if (match) return true;
        }
      }
      return false;
    };

    ~Star() override {
      // Nothing
    };

  };


  class Word: public RegExp {
    std::unique_ptr<std::string> center;
   public:
    Word(const std::string &s): center{std::move(new std::string(s))} {};
    Word(std::string &&s): center{new std::string(s)} {};
    bool matches (const std::string s) override {
      if (center->compare(s) == 0) { return true; }
      return false;
    }

    ~Word() override {
      // Nothing
    };


  };
}
#endif

