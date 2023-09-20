#include <unistd.h>
#include <memory>
#include <tuple>
#include <vector>
#include <bits/stdc++.h>

#include "gameRunner.h"
#include "../view/cursesView.h"
#include "../controller/cursesControl.h"
#include "../object/frame.h"
#include "../object/gameObject.h"
#include <iostream>
#include <chrono>


GameRunner::GameRunner() {
   setView(std::move(std::make_unique<CursesView>(*this)));
   setController(std::move(std::make_unique<CurseKeyboard>()));
   addStatus(0, "Ticks", 0);
}

void GameRunner::update() {
   int n = objects.size();
   for (int i = 0; i < n; i++) {
      objects[i]->runBehaviours();
   }
}

void GameRunner::del() {
   std::sort(delque.begin(), delque.end(), std::greater<int>());
}

void GameRunner::play() {
   while (1) {
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

      if (objects.at(0)->getX() != 76 || objects.at(0)->getY() != 2) {
         displayViews();
      } else {
         displayWin();
      }
      update();

      status.at(0)->incDisp(1);

      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

      int timeSpent = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
      usleep(500000-timeSpent);
   }
}


void GameRunner::setFrame(int x) {
   frame = std::make_unique<Frame>(x);
}


int GameRunner::addObject(int x, int y, int height, char c) {
   objects.emplace_back(std::make_unique<GameObject>(x,y,height,c));
   return (objects.size()-1);
}


int GameRunner::addObject(int x, int y, int w, int h, int height, char c) {
   objects.emplace_back(std::make_unique<GameObject>(x,y,w,h,height,c));
   return (objects.size()-1);
}

int GameRunner::addObject(std::vector<std::tuple<int, int, char>> vec, int h) {
   objects.emplace_back(std::make_unique<GameObject>(vec, h));
   return (objects.size()-1);
}

void GameRunner::addStatus(int t, std::string w, int n) {
   status.emplace_back(std::make_unique<Status>(t,w,n));
}


void GameRunner::attachBehaviour(int id, int type, int x, int y, int c) {
   if (id < static_cast<int>(objects.size())) {
      objects.at(id)->addBehaviour(type, x, y, *this, c);
   }
}


bool GameRunner::checkCollision(int x, int y, int h) {
   for (auto &object: objects) {
      if (object->contains(x,y,h)) { return true; }
   }
   if (frame->contains(x,y,h)) { return true; }
   return false;
}

void GameRunner::addDelque(int id) {
   delque.push_back(id);
}


std::vector<std::tuple<int, int, int, char>> GameRunner::getObjects() {
   std::vector<std::tuple<int, int, int, char>> ret_vec;

   if (objects.size() >= 1){
     for (auto &object: objects) {
        std::vector<std::tuple<int, int, int, char>> pixels = object->pixelData();
        for (auto &pixel: pixels) {
           ret_vec.push_back(pixel);
        }
     }
   }
   std::vector<std::tuple<int, int, int, char>> pix = frame->pixelData();
   for (auto &pixel: pix) {
      ret_vec.push_back(pixel);
   }
   return ret_vec;
}

std::vector<std::string> GameRunner::getStatus() {
   std::vector<std::string> ret_vec;
   if (status.size() >= 1) {
     for (auto &stat: status) {
        ret_vec.push_back(stat->getStatus());
     }
  }
  return ret_vec;

}
