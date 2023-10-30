#ifndef TIMER_HPP
#define TIMER_HPP

#include <string>
#include <chrono>
#include <map>

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

  micro asMicro();
  milli asMilli();
  secs asSecs();
private:
  time_point init;
  time_point time_paused;
  bool paused;
  bool started;
};

#endif // !TIMER_HPP
