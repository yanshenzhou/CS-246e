#include "model/model.h"
#include "model/gameRunner.h"


#include <vector>
#include <tuple>
#include <random>

int main() {
   GameRunner *x = new GameRunner();
   x->setFrame(1);

   x->addStatus(0,"Level",1);
   x->addStatus(1,"CURRENTLY PLAYING: Super fun maze game!!", 2);


   std::vector<std::tuple<int,int,char>> c_shape;

   c_shape.push_back(std::make_tuple(24,20,'_'));
   c_shape.push_back(std::make_tuple(23,20,'_'));
   c_shape.push_back(std::make_tuple(22,20,'_'));
   c_shape.push_back(std::make_tuple(21,20,'_'));
   c_shape.push_back(std::make_tuple(20,20,'_'));
   c_shape.push_back(std::make_tuple(19,21,'('));
   c_shape.push_back(std::make_tuple(20,21,'_'));
   c_shape.push_back(std::make_tuple(20,22,'('));
   c_shape.push_back(std::make_tuple(21,22,'_'));
   c_shape.push_back(std::make_tuple(22,22,'_'));
   c_shape.push_back(std::make_tuple(23,22,')'));
   c_shape.push_back(std::make_tuple(23,21,'_'));
   c_shape.push_back(std::make_tuple(24,21,'_'));
   c_shape.push_back(std::make_tuple(25,21,')'));


   auto player = x->addObject(1, 20, 1, 'h');
   x->addObject(76, 2, 10, '!');
   x->addObject(7, 13, 1, 13, 1, '#');
   x->addObject(7, 13, 20, 1, 1, '#');
   x->addObject(20, 0, 1, 10, 1, '#');
   x->addObject(20, 10, 1, 3, 3, '&');
   x->addObject(40, 0, 3, 15, 1, '#');
   x->addObject(72, 5, 7, 3, 1, '#');

   auto cloud1 = x->addObject(c_shape, 4);
   auto cloud2 = x->addObject(c_shape, 4);
   x->addObject(7, 13, 7, 1, 1, '#');

   std::random_device rd;
   std::mt19937 rng(rd());
   std::uniform_int_distribution<int> uni(0, 20);

   for (int i = 0; i < 10; i++) {
     auto a = x->addObject(i*-20, uni(rng), 2, '>');
     x->attachBehaviour(a, 1, 1, 0, 0);
   }

   x->attachBehaviour(player, 3, 0, 1, 0);
   x->attachBehaviour(cloud1, 2, 0, 0, 0);
   x->attachBehaviour(cloud2, 1, 1, -1, 0);
   x->play();


}
