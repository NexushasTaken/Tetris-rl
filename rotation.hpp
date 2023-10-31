#pragma once

enum struct Rotate {
  CW, // ClockWise
  CCW, // CounterClockWise
  Last,
};

inline Rotate rotateInverse(Rotate rt) {
  return (Rotate)((int)rt & 1 ? (int)rt-1 : (int)rt+1);
}
