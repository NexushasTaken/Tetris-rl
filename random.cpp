#include "random.hpp"
#include <raylib.h>
#include <cmath>

Random::Random() : gen(rd()) {}

int Random::randomInt(int min, int max) {
  if (min > max) {
    return 0;
  }

  int rand_value = std::abs((int)this->gen());
  int interval = max - min;
  return min + (rand_value % (interval+1));
}

void Random::setSeed(seed seed) {
  this->gen.seed(seed);
}
