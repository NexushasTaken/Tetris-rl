#pragma once

#include <vector>
#include <stack>
#include "tetrimino.hpp"
#include "direction.hpp"
#include "rotation.hpp"

// Tetris Matrix
struct Maytrix {
  Maytrix();
  void draw(float x, float y, float mino_size);
  void tetriminoMove(Direction dt);
  bool tetriminoIsCollided();
  void tetriminoReset();
  void tetriminoRotate(Rotate rt);
  bool isOccupied(int row, int col);
  Vector2 calculateMinoPosition(
      float offx, float offy,
      int column, int row,
      float mino_size);
  bool tetriminoPlaced();
  BufferAreaIterator begin();
  BufferAreaIterator end();

  std::stack<Direction> mino_moved;
  std::stack<Rotate> mino_rotate;
  Tetrimino tetrimino;
  BufferArea buffer_area;
};
