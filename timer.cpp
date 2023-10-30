#include <iostream>
#include <chrono>
#include <cmath>
#include "timer.hpp"

using namespace std::chrono;

void Timer::start() {
  if (started)
    return;
  init = clock::now();
  started = true;
}

void Timer::reset() {
  started = false;
  paused = false;
}

void Timer::pause() {
  if (!started || paused)
    return;
  paused = true;
  time_paused = clock::now();
}

void Timer::unpause() {
  if (!started || !paused)
    return;
  init += clock::now() - time_paused;
  paused = false;
}

bool Timer::toggle() {
  if (!started)
    return false;
  if (paused)
    unpause();
  else
    pause();
  return isPaused();
}

bool Timer::isPaused() {
  if (!started)
    return false;
  return paused;
}

Timer::micro Timer::asMicro() {
  if (!started)
    return Timer::micro{0};

  time_point now = paused ? time_paused : clock::now();
  return std::chrono::duration_cast<micro>(now - init);
}

Timer::milli Timer::asMilli() {
  if (!started)
    return Timer::milli{0};
  return std::chrono::duration_cast<milli>(asMicro());
}

Timer::secs Timer::asSecs() {
  if (!started)
    return Timer::secs{0};
  return std::chrono::duration_cast<secs>(asMicro());
}
