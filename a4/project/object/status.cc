
#include "status.h"


std::string Status::getStatus() {
   if (type == 1) {
      return (word);
   } else {
      std::string space = ": ";
      return (word + (space += std::to_string(num)));
   }

}
