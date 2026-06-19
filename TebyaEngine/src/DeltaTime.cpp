#include "Tebya/DeltaTime.hpp"

namespace tebya {

DeltaTime::DeltaTime(int fps)
    : /*targetFPS(fps),*/ targetFrameTime(1.0f / fps) {
  lastFrameTime = SDL_GetTicks();
  dt = 0.0f;
}

void DeltaTime::update() {
  Uint32 currentFrameTime = SDL_GetTicks();
  dt = (currentFrameTime - lastFrameTime) / 1000.0f;
  lastFrameTime = currentFrameTime;
}

float DeltaTime::deltaTime() const { return dt; }

void DeltaTime::capFPS() {
  Uint32 frameEnd = SDL_GetTicks();
  float frameTime = (frameEnd - lastFrameTime) / 1000.0f;

  if (frameTime < targetFrameTime) {
    Uint32 delayTime = (targetFrameTime - frameTime) * 1000;
    SDL_Delay(delayTime);
  }
}

} // namespace tebya