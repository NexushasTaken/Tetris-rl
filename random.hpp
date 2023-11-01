#pragma once

#include <random>

struct Random {
  using mt = std::mt19937;
  using seed = mt::result_type;
  using random_device = std::random_device;
  Random();
  // both min and max are inclusive
  int randomInt(int min, int max);
  void setSeed(seed seed);
private:
  random_device rd;
  mt gen;
};
