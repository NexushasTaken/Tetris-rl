#include <chrono>
#include "timer.hpp"

using namespace std::chrono;

void Timer::start() {
  if (this->started)
    return;
  this->init = clock::now();
  this->started = true;
}

void Timer::reset() {
  this->started = false;
  this->paused = false;
}

void Timer::pause() {
  if (!this->started || this->paused)
    return;
  this->paused = true;
  this->time_paused = clock::now();
}

void Timer::unpause() {
  if (!this->started || !this->paused)
    return;
  this->init += clock::now() - this->time_paused;
  this->paused = false;
}

bool Timer::toggle() {
  if (!this->started)
    return false;
  if (this->paused)
    this->unpause();
  else
    this->pause();
  return this->isPaused();
}

bool Timer::isPaused() {
  if (!this->started)
    return false;
  return this->paused;
}

void Timer::addTime(micro time) {
  if (!this->started)
    return;
  this->init -= time;
}

Timer::micro Timer::asMicro() {
  if (!this->started)
    return Timer::micro{0};

  time_point now = this->paused ? this->time_paused : clock::now();
  return std::chrono::duration_cast<micro>(now - this->init);
}

Timer::milli Timer::asMilli() {
  if (!this->started)
    return Timer::milli{0};
  return std::chrono::duration_cast<milli>(this->asMicro());
}

Timer::secs Timer::asSecs() {
  if (!this->started)
    return Timer::secs{0};
  return std::chrono::duration_cast<secs>(this->asMicro());
}
