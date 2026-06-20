#pragma once

#include <SDL2/SDL_rect.h>
namespace Asteroids {

struct vec2 {
  float x, y;
};

inline float dist2rects_sq(const SDL_FRect &a, const SDL_FRect &b) {
  float dx = (a.x + a.w * 0.5f) - (b.x + b.w * 0.5f);
  float dy = (a.y + a.h * 0.5f) - (b.y + b.h * 0.5f);
  return dx * dx + dy * dy; // no sqrt = caller compares against threshold²
}

inline float degreeToRad(float angle_degrees) {
  constexpr float to_rad = M_PI / 180.0f;
  return angle_degrees * to_rad;
}

inline float radToDegree(float angle_rad) {
  constexpr float to_rad = 180.0f / M_PI;
  return angle_rad * to_rad;
}

} // namespace Asteroids