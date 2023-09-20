#include <tuple>

#include "pixel.h"

std::tuple<int, int, int, char> Pixel::getPixel() {
   return std::make_tuple(x_pos, y_pos, height, rep);
}
