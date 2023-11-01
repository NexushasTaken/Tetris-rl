#pragma once
#include <chrono>

using namespace std::chrono_literals;

namespace Time {
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;
  using clock = std::chrono::steady_clock;
  using s = std::chrono::seconds;
  using ms = std::chrono::milliseconds;
  using us = std::chrono::microseconds;

  struct Timer {
    void start();
    void restart();
    void reset();
    void pause();
    void unpause();
    bool isStarted();
    bool toggle();
    bool isPaused();
    void addTime(Time::us time);

    Time::us asMicro();
    Time::ms asMilli();
    Time::s asSecs();
  private:
    Time::time_point init;
    Time::time_point time_paused;
    bool paused = false;
    bool started = false;
  };

  struct IncrementalTimer {
    void start(Time::us delay);
    void reset();
    void restart();
    bool isStarted();
    bool isElapsed(bool decr=false);
    Time::us asMicro();
  private:
    Time::Timer timer;
    Time::us delay = 1us;
  };
}
