#pragma once

#include <vector>
#include "tetrimino.hpp"

// Tetris Matrix
struct TMatrix {
  TMatrix();
  void draw(float x, float y, float mino_size);
  MatrixDSIterator begin();
  MatrixDSIterator end();

  Tetrimino tetrimino;
  MatrixDS buffer_zone;
};
