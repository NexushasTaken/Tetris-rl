#include <iostream>
#include <limits>
#include <thread>
#include <utility>
#include "../random.hpp"
#include "../time.hpp"

int main() {
  Random random;
  int min = 10;
  int max = 16;
  int current_min = std::numeric_limits<int>::max();
  int current_max = std::numeric_limits<int>::min();
  while (current_min != min || current_max != max) {
    current_min = std::min(random.randomInt(min, min), current_min);
    current_max = std::max(random.randomInt(min, max), current_max);
    std::cout << current_min << ", " << current_max << std::endl;
  }
  return 0;
}
