#include "model.h"

void Model::setView(std::unique_ptr<View> v) {
   view = std::move(v);
}

void Model::setController(std::unique_ptr<Controller> c) {
   control = std::move(c);
}

void Model::displayViews() {
   view->render();
}

void Model::displayWin() {
   view->wins();
}

int Model::getKey() {
   return (control->getAction());
}
