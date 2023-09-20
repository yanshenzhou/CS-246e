#include "frame.h"

Frame::Frame (int type) {
   if (type == 0) { // Light Border
      for (int x = 1; x < 79; ++x) {
        addPixel(x, 0, 0,'-');
        addPixel(x, 21, 0, '-');
      }
      for (int y = 1; y < 21; ++y) {
        addPixel(0, y, 0, '|');
        addPixel(79, y, 0, '|');
      }
      addPixel(0, 0, 0, '+');
      addPixel(0, 21, 0, '+');
      addPixel(79, 0, 0, '+');
      addPixel(79, 21, 0, '+');
   } else { // Heavy Border
      for (int x = 1; x < 79; ++x) {
         addPixel(x, 0, 1, '=');
         addPixel(x, 21, 1, '=');
      }
      for (int y = 1; y < 21; ++y) {
         addPixel(0, y, 1, '\\');
         addPixel(79, y, 1, '\\');
      }
      addPixel(0, 0, 1, '&');
      addPixel(0, 21, 1, '&');
      addPixel(79, 0, 1, '&');
      addPixel(79, 21, 1, '&');
   }
}
