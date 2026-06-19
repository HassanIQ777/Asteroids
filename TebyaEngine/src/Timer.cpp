#include "Tebya/Timer.hpp"

namespace tebya {

Timer::Timer() { p_start(); }
Timer::Timer(const double &start_time) : p_total_elapsed(start_time) {
  p_start();
}

void Timer::pause() {
  if (p_running) {
    auto now = std::chrono::high_resolution_clock::now();
    p_total_elapsed +=
        std::chrono::duration<double>(now - p_start_time).count();
    p_running = false;
  }
}

void Timer::resume() { p_start(); }

double Timer::elapsed() const {
  if (p_running) {
    auto now = std::chrono::high_resolution_clock::now();
    return p_total_elapsed +
           std::chrono::duration<double>(now - p_start_time).count();
  }
  return p_total_elapsed;
}

void Timer::reset() {
  p_total_elapsed = 0.0;
  p_running = false;
}

void Timer::restart() {
  p_total_elapsed = 0.0;
  // keep running
  p_running = true;
  p_start_time = std::chrono::high_resolution_clock::now();
}

void Timer::p_start() {
  if (!p_running) {
    p_running = true;
    p_start_time = std::chrono::high_resolution_clock::now();
  }
}

} // namespace tebya