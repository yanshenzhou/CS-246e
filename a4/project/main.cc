#include "model/model.h"
#include "model/gameRunner.h"

#include <vector>
#include <tuple>

int main() {

   GameRunner *x = new GameRunner();
   x->setFrame(0);

   x->addStatus(0,"Lives",2);
   x->addStatus(1,"CURRENTLY PLAYING!", 2);


   auto a = x->addObject(20, 12, 1, 'e');
   x->addObject(30, 10, 10, 5, 1, '+');

   std::vector<std::tuple<int, int, char>> nums;
   nums.push_back(std::make_tuple(45, 11, '1'));
   nums.push_back(std::make_tuple(46, 12, '2'));
   nums.push_back(std::make_tuple(47, 13, '3'));

   x->addObject(nums, 1);

   x->attachBehaviour(a,1,1,0,0);
   x->attachBehaviour(a,3,1,1,0);

   x->play();
}
