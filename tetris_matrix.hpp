#pragma once

#include <vector>
#include <stack>
#include "time.hpp"
#include "tetrimino.hpp"
#include "direction.hpp"
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
  bool tetriminoMove(Direction dt, int count=1);
  bool tetriminoRotate(Rotate rt);
  bool tetriminoCanMove(Direction dt);
  bool tetriminoCanRotate(Rotate rt);

  BufferAreaIterator begin();
  BufferAreaIterator end();

  Tetrimino tetrimino;
  BufferArea buffer_area;
};
