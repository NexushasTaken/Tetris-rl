#pragma once

#include <vector>
#include <stack>
#include "time.hpp"
#include "tetrimino.hpp"
#include "axis.hpp"
#include "rotation.hpp"

// Tetris Matrix
struct Maytrix {
  Maytrix();
  void update();
  bool tetriminoIsCollided();
  void tetriminoPlace(TetriminoShape next);
  void removeClearedLines();
  bool isMinoOccupied(int row, int col);
  // Return move count
  int moveToSurface();
  void moveToRow(int count);
  void restart();

  bool tetriminoIsOnSurface();
  bool tetriminoMove(Axis dt, int count);
  bool tetriminoRotate(Rotate rt);
  bool tetriminoCanMove(Axis dt, int count);
  bool tetriminoCanRotate(Rotate rt);

  BufferAreaIterator begin();
  BufferAreaIterator end();

  Tetrimino tetrimino;
  BufferArea buffer_area;
};
