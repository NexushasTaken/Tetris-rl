#pragma once
#include <queue>
#include <list>
#include "random.hpp"
#include "time.hpp"
#include "tetris_matrix.hpp"

struct Tetris {
  Tetris(float mino_size, Vector2 offset);
  void update();
  void draw();

  bool isLockedOut();
  void holdCurrent();

  TetriminoShape getNextShape();
  TetriminoShape getRandomShape();

  void setGameOver();
  void resetTimers();
  void restart();

  void startLockedDown(Time::us delay, bool force);
  void fillBag();
  Vector2 calculateMinoPosition(
      float offx, float offy,
      int column, int row,
      float mino_size);

  Maytrix maytrix;
  TetriminoShape holded_shape;
  bool can_hold;
  std::list<TetriminoShape> bag;
  Time::IncrementalTimer classic_drop_timer;
  Time::IncrementalTimer locked_down_timer;
  Time::IncrementalTimer soft_drop_timer;
  Time::IncrementalTimer auto_repeat_timer;
  Time::IncrementalTimer auto_repeat_delay_timer;
  bool game_over;
  Random random;

  Time::us hard_locked_down_speed = 10us;
  Time::us classic_locked_down_speed = 500ms;
  Time::us fall_speed = 500ms;
  Time::us fall_speed_multiplier = 20ms; // used for soft drop
  Time::us auto_repeat_speed = 100ms;
  Time::us auto_repeat_delay_speed = 300ms;
  float mino_size;
  Vector2 offset;
};
