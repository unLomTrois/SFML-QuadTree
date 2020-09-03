#include "random.hpp"
#include <stdlib.h>
#include <time.h>

int random(int max) {
  int min = 0;
  static bool first = true;
  if (first) {
    std::srand(time(NULL));  // seeding for the first time only!
    first = false;
  }

  return min + std::rand() % (max + 1 - min);
}

int random(int min, int max) {
  static bool first = true;
  if (first) {
    std::srand(time(NULL));  // seeding for the first time only!
    first = false;
  }

  return min + std::rand() % (max + 1 - min);
}
