
#include "behaviour.h"
#include "../object/interactableObject.h"
#include "../model/gameRunner.h"

Behaviour::Behaviour(int b_type, int x, int y, InteractableObject &obj, GameRunner &mod, int c_type): b_type{b_type}, x{x}, y{y}, obj{obj}, mod{mod}, c_type{c_type} {}

void Behaviour::tryMove(int tx, int ty) {
   if (mod.checkCollision(obj.getX()+tx,obj.getY()+ty,obj.getH())) {
      if (c_type == 1) {
         x = x*-1;
         y = y*-1;
      }
   } else {
      obj.moveObject(tx,ty);
   }
}

void Behaviour::update() {
   if (b_type == 1) {
      tryMove(x,y);
   } else if (b_type == 2) {
      int c_x = obj.getX();
      int c_y = obj.getY();

      int vec_x = 0;
      int vec_y = 0;

      if (c_x < x) { vec_x = 1; }
      else if (c_x > x) { vec_x = -1; }

      if (c_y < x) { vec_y = 1; }
      else if (c_y > x) { vec_y = -1; }

      tryMove(vec_x,vec_y);
   } else if (b_type == 3) {
      int press = mod.getKey();

      if (press == 'w') { tryMove(0,-1); }
      else if (press == 'a') { tryMove(-1, 0); }
      else if (press == 's') { tryMove(0, 1); }
      else if (press == 'd') { tryMove(1, 0); }

      else if (press == ' ') {
         int bullet = mod.addObject(obj.getX(), obj.getY()-1, 1, '^');
         mod.attachBehaviour(bullet, 1, 0, -1, 1);
      }
   }
}
