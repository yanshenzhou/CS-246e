#include <memory>
#include <vector>
#include <tuple>
#include <iostream>

#include "interactableObject.h"
#include "../behaviours/behaviour.h"
#include "../model/gameRunner.h"

void InteractableObject::addPixel(int x, int y, int h, char r) {
   pixels.emplace_back(std::make_unique<Pixel>(x,y,h,r));
}

void InteractableObject::moveObject (int x_change, int y_change) {
   for (auto &pixel: pixels) {
      pixel->moveX(x_change);
      pixel->moveY(y_change);
   }
}

int InteractableObject::getX() {
   if (pixels.size() > 0) {
      return std::get<0>(pixels.at(0)->getPixel());
   } else { return 0; }
}

int InteractableObject::getY() {
   if (pixels.size() > 0) {
      return std::get<1>(pixels.at(0)->getPixel());
   } else { return 0; }
}

int InteractableObject::getH() {
   if (pixels.size() > 0) {
      return std::get<2>(pixels.at(0)->getPixel());
   } else { return 0; }
}

void InteractableObject::addBehaviour(int type, int x, int y, GameRunner &mod, int c) {
   behaviours.emplace_back(std::make_unique<Behaviour>(type,x,y, *this, mod, c));
}

void InteractableObject::runBehaviours() {
   if (behaviours.size() > 0) {
      for (auto &behaviour: behaviours) {
         behaviour->update();
      }
   }
}

bool InteractableObject::contains(int x, int y, int h) {
   for (auto &pix: pixels) {
     if (pix->contains(x,y,h)) {
       return true;
     }
   }
   return false;
}

std::vector<std::tuple<int, int, int, char>> InteractableObject::pixelData() {
   std::vector<std::tuple<int, int, int, char>> ret_vec;

   for (auto &pixel: pixels) {
      ret_vec.emplace_back(pixel->getPixel());
   }
   return ret_vec;
}
