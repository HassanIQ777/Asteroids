#pragma once

#include <deque>

namespace tebya {

class FPSCounter {
  std::deque<double> frameTimes; // Stores last frame times
  double timeSum = 0.0;          // Sum of last frame times
  size_t maxFrames;              // Maximum number of stored frames

public:
  FPSCounter(size_t maxFrames_ = 60);

  // update this at the start of every frame
  void update(double deltaTime);

  double getFPS() const;

  // Sets how many frame times are stored, higher values = less fluctuations
  void setMaxFrames(size_t fps) { maxFrames = fps; }
};

} // namespace tebya