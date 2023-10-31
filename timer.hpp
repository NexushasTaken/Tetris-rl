#pragma once
#include <chrono>

struct Timer {
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;
  using clock = std::chrono::steady_clock;
  using secs = std::chrono::seconds;
  using milli = std::chrono::milliseconds;
  using micro = std::chrono::microseconds;

  void start();
  void reset();
  void pause();
  void unpause();
  bool toggle();
  bool isPaused();
  void addTime(micro time);

  micro asMicro();
  milli asMilli();
  secs asSecs();
private:
  time_point init;
  time_point time_paused;
  bool paused = false;
  bool started = false;
};
