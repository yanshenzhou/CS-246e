#ifndef STA
#define STA

#include <string>


/*
   The status bar, has two different types and allows for intergers and words to be rendered
*/
class Status {
    int type;
    std::string word;
    int num;

   public:
    Status(int t, std::string w, int n): type{t}, word{w}, num{n} {};

    void setDisp(std::string w) { word = w; }
    void incDisp(int y) { num += y; }

    std::string getStatus();
};
#endif
