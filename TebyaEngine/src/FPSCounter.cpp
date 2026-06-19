#include "Tebya/FPSCounter.hpp"

namespace tebya {

FPSCounter::FPSCounter(size_t maxFrames_) : maxFrames(maxFrames_) {}

// update this at the start of every frame
void FPSCounter::update(double deltaTime) {
  frameTimes.push_back(deltaTime);
  timeSum += deltaTime;

  // Remove old frames if exceeding maxFrames
  if (frameTimes.size() > maxFrames) {
    timeSum -= frameTimes.front();
    frameTimes.pop_front();
  }
}

double FPSCounter::getFPS() const {
  // FPS = number of frames stored / total time covered
  return timeSum > 0.0 ? frameTimes.size() / timeSum : 0.0;
}

} // namespace tebya