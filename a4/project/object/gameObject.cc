
#include "gameObject.h"

GameObject::GameObject(int x, int y, int height, char c) {
   addPixel(x,y,height,c);
}

GameObject::GameObject(int x, int y, int w, int h, int height, char c) {
   for (int x_pos = x; x_pos < x+w; x_pos++) {
      for (int y_pos = y; y_pos < y+h; y_pos++) {
         addPixel(x_pos, y_pos, height, c);
      }
   }
}

GameObject::GameObject(std::vector<std::tuple<int, int, char>> vec, int height) {
   for (auto &item: vec) {
      addPixel(std::get<0>(item), std::get<1>(item), height, std::get<2>(item));
   }
}
