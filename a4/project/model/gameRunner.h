#ifndef GAME
#define GAME

#include <memory>
#include <tuple>
#include <vector>
#include <string>

#include "model.h"
#include "../object/frame.h"
#include "../object/gameObject.h"
#include "../object/status.h"

/*
   The concrete class for our game runner, it has a series of fields that hold the frame, all the objects, the status bars and a
      deletion queue which is meant for deleting some objects. Since this is what the user interfaces with we have the ability to addObjects
      give thoses objects behaviours and add status bars, also the ability to run the game via play()
*/

class GameRunner: public Model {
   std::unique_ptr<Frame> frame;
   std::vector<std::unique_ptr<GameObject>> objects;
   std::vector<std::unique_ptr<Status>> status;
   std::vector<int> delque;

  protected:
   void update();
   void del();

  public:
   GameRunner();

   void play();
   void setFrame(int x);

   int addObject(int x, int y, int height, char c);
   int addObject(int x, int y, int w, int h, int height, char c);
   int addObject(std::vector<std::tuple<int, int, char>> vec, int height);

   void addStatus(int y, std::string w, int n);
   void attachBehaviour(int id, int type, int x, int y, int c);

   bool checkCollision(int x, int y, int h);

   void addDelque(int id);

   std::vector<std::tuple<int, int, int, char>> getObjects();
   std::vector<std::string> getStatus();
};
#endif
