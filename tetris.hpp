#pragma once
#include <queue>
#include "random.hpp"
#include "time.hpp"
#include "tetris_matrix.hpp"

struct Tetris {
  Tetris();
  void update();
  void draw();

  bool isLockedOut();

  TetriminoShape getNextShape();
  TetriminoShape getRandomShape();

  void setGameOver();
  void startLockedDown(Time::us time);
  void stopLockedDown();
  void resetTimers();
  void restart();

  void fillBag();
  Vector2 calculateMinoPosition(
      float offx, float offy,
      int column, int row,
      float mino_size);

  Maytrix maytrix;
  std::queue<TetriminoShape> bag;
  Time::Timer snap_timer;
  Time::Timer locked_down_timer;
  Time::us locked_down_time;
  bool game_over;
  Random random;

  const float mino_size;
  const Vector2 offset;
};
