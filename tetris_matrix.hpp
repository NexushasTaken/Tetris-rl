#pragma once

#include <vector>
#include <stack>
#include "tetrimino.hpp"
#include "direction.hpp"

// Tetris Matrix
struct Maytrix {
  Maytrix();
  void draw(float x, float y, float mino_size);
  void tetriminoMove(Direction dt);
  bool tetriminoIsCollided();
  void tetriminoReset();
  bool isOccupied(int row, int col);
  bool tetriminoPlaced();
  BufferAreaIterator begin();
  BufferAreaIterator end();

  std::stack<Direction> mino_moved;
  Tetrimino tetrimino;
  BufferArea buffer_area;
};
