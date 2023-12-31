#include "time.hpp"

namespace Time {
  void Timer::start() {
    if (this->started)
      return;
    this->init = clock::now();
    this->started = true;
  }

  void Timer::restart() {
    this->init = clock::now();
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

  bool Timer::isStarted() {
    return this->started;
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

  void Timer::addTime(Time::us time) {
    if (!this->started)
      return;
    this->init -= time;
  }

  Time::us Timer::asMicro() {
    if (!this->started)
      return Time::us{0};

    time_point now = this->paused ? this->time_paused : clock::now();
    return std::chrono::duration_cast<Time::us>(now - this->init);
  }

  Time::ms Timer::asMilli() {
    if (!this->started)
      return Time::ms{0};
    return std::chrono::duration_cast<Time::ms>(this->asMicro());
  }

  Time::s Timer::asSecs() {
    if (!this->started)
      return Time::s{0};
    return std::chrono::duration_cast<Time::s>(this->asMicro());
  }


  void IncrementalTimer::start(Time::us delay) {
    if (this->isStarted()) {
      return;
    }
    Timer::start();
    this->delay = delay;
  }

  void IncrementalTimer::reset() {
    Timer::reset();
    this->delay = 1us;
  }

  void IncrementalTimer::update() {
    if (this->beforeCallback != nullptr) {
      this->beforeCallback(*this);
    }
    if (this->isElapsed()) {
      if (this->callback != nullptr) {
        this->callback(*this);
      }
      if (this->resetAfterElapsed) {
        this->reset();
      }
    }
  }

  void IncrementalTimer::setCallback(Callback cb) {
    this->callback.swap(cb);
  }

  void IncrementalTimer::setBeforeCallback(Callback cb) {
    this->beforeCallback.swap(cb);
  }

  void IncrementalTimer::setResetAfterElapsed(bool reset) {
    this->resetAfterElapsed = reset;
  }

  bool IncrementalTimer::isElapsed() {
    if (!this->isStarted()) {
      return false;
    }

    if (this->asMicro() > this->delay) {
      if (this->isContinous()) {
        this->addTime(-this->delay);
      }
      return true;
    }
    return false;
  }

  bool IncrementalTimer::isContinous() {
    return !this->resetAfterElapsed;
  }
}
