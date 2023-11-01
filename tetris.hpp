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
  void resetTimers();
  void restart();

  void fillBag();
  Vector2 calculateMinoPosition(
      float offx, float offy,
      int column, int row,
      float mino_size);

  Maytrix maytrix;
  std::queue<TetriminoShape> bag;
  Time::IncrementalTimer snap_timer;
  Time::IncrementalTimer locked_down_timer;
  Time::IncrementalTimer soft_drop_timer;
  Time::IncrementalTimer auto_repeat_timer;
  Time::IncrementalTimer auto_repeat_delay_timer;
  bool game_over;
  Random random;

  const Time::us hard_drop_speed = 10us;
  const Time::us classic_drop_speed = 500ms;
  const Time::us fall_speed = 500ms;
  const Time::us auto_repeat_speed = 500ms;
  const Time::us auto_repeat_delay_speed = 300ms;
  const float mino_size;
  const Vector2 offset;
};
