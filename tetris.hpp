#pragma once
#include <queue>
#include "timer.hpp"
#include "tetris_matrix.hpp"

struct Tetris {
  Tetris();
  void draw();
  Vector2 calculateMinoPosition(
      float offx, float offy,
      int column, int row,
      float mino_size);

  Maytrix maytrix;
  std::queue<TetriminoShape> bag;
  Timer fall_timer;

  const float mino_size;
  const Vector2 offset;
};
