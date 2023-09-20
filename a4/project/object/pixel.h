#ifndef PIX
#define PIX

#include <tuple>

/*
   Our most basic single character object, each object is made up of series of them
*/
class Pixel {
    int x_pos;
    int y_pos;
    int height;
    char rep;
   public:
    Pixel(int x, int y, int h, char r): x_pos{x}, y_pos{y}, height{h}, rep{r} {};

    void moveX(int x) { x_pos += x; }
    void moveY(int y) { y_pos += y; }
    bool contains(int x, int y, int h) { return ((x==x_pos) && (y==y_pos) && (h==height)); }
    std::tuple<int, int, int, char> getPixel();
};
#endif
