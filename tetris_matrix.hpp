#pragma once

#include <vector>
#include <stack>
#include "tetrimino.hpp"
#include "direction.hpp"
#include "rotation.hpp"

// Tetris Matrix
struct Maytrix {
  Maytrix();
  void tetriminoMove(Direction dt);
  bool tetriminoIsCollided();
  void tetriminoReset();
  void tetriminoSwap(TetriminoShape shape);
  void tetriminoRotate(Rotate rt);
  bool isOccupied(int row, int col);
  bool hardDrop(TetriminoShape next = TetriminoShape::O);
  // Return fall count
  int drop();
  void undrop(int count);
  BufferAreaIterator begin();
  BufferAreaIterator end();

  std::stack<Direction> mino_moved;
  std::stack<Rotate> mino_rotate;
  Tetrimino tetrimino;
  BufferArea buffer_area;
};
