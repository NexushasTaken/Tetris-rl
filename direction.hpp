#pragma once

#include <array>

enum struct Direction {
  Up, Down, Left, Right, Last,
};

inline Direction directionInverse(Direction dt) {
  return (Direction)((int)dt & 1 ? (int)dt-1 : (int)dt+1);
}

inline std::array<Direction, 4> __direction_inverse = {
  Direction::Down, Direction::Up, Direction::Right, Direction::Left,
};

#define DIRECTION_INVERSE(T) (__direction_inverse[(int)T])
