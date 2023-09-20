#include "model/model.h"
#include "model/gameRunner.h"

#include <random>

int main() {
   GameRunner *x = new GameRunner();
   x->setFrame(0);

   x->addStatus(0,"Lives",2);
   x->addStatus(1,"NOW PLAYING: Space Invaders", 2);

   auto player = x->addObject(10, 20, 1, 'h');
   x->addObject(10, 15, 1, 'e');
   x->addObject(50, 10, 1, 'e');
   x->addObject(78, 2, 1, 'e');


   auto f1 = x->addObject(-5,-10,1, '*');
   auto f2 = x->addObject(80, 2, 1, '*');

   x->addObject(30, 5, 1, 'v');
   auto d1 = x->addObject(5, 5, 1, '>');
   auto d2 = x->addObject(70, 5, 1, '<');

   auto t1 = x->addObject(0, 13, 1, 't');
   auto t2 = x->addObject(0, 7, 1, 't');

   x->attachBehaviour(player, 3, 0, 0, 0);
   x->attachBehaviour(f1, 1, 1, 1, 1);
   x->attachBehaviour(f2, 1, -1, 1, 1);
   x->attachBehaviour(d1, 1, 1, 0, 1);
   x->attachBehaviour(d2, 1, -1, 0, 0);

   x->attachBehaviour(t1, 2, 20, 90, 0);
   x->attachBehaviour(t2, 2, 11, 90, 0);

   std::random_device rd;
   std::mt19937 rng(rd());
   std::uniform_int_distribution<int> uni(0, 77);

   for (int i = 0; i < 20; i++) {
      auto t = x->addObject(uni(rng), i*-10, 1, '.');
      x->attachBehaviour(t, 1, 0, 1, 1);
   }

   x->play();


}
