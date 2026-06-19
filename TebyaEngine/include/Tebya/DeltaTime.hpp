#pragma once

#include <SDL2/SDL.h>

namespace tebya {

class DeltaTime {
private:
  Uint32 lastFrameTime;
  float dt;
  // const int targetFPS;
  float targetFrameTime; // time per frame in seconds

public:
  DeltaTime(int fps = 60);

  void update();

  float deltaTime() const;

  void capFPS();
  void setMaxFPS(int fps) { targetFrameTime = 1.0f / fps; }
};

} // namespace tebya