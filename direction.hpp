#pragma once

enum struct Direction {
  Up, Down, Left, Right, Last,
};

inline Direction directionInverse(Direction dt) {
  return (Direction)((int)dt & 1 ? (int)dt-1 : (int)dt+1);
}
