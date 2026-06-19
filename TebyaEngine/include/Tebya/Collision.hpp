#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

namespace tebya {

enum class CollisionSide { None, Left, Right, Top, Bottom };

class Collision {
public:
  static CollisionSide AABB(const SDL_FRect &a, const SDL_FRect &b) {
    // centers
    float aCenterX = a.x + a.w * 0.5f;
    float aCenterY = a.y + a.h * 0.5f;
    float bCenterX = b.x + b.w * 0.5f;
    float bCenterY = b.y + b.h * 0.5f;

    // distances between centers
    float dx = bCenterX - aCenterX;
    float dy = bCenterY - aCenterY;

    // half sizes
    float halfW = (a.w + b.w) * 0.5f;
    float halfH = (a.h + b.h) * 0.5f;

    // check collision
    if (std::abs(dx) >= halfW || std::abs(dy) >= halfH)
      return CollisionSide::None;

    // penetration depth
    float overlapX = halfW - std::abs(dx);
    float overlapY = halfH - std::abs(dy);

    // resolve along smallest axis
    if (overlapX < overlapY) {
      return (dx > 0) ? CollisionSide::Right : CollisionSide::Left;
    } else {
      return (dy > 0) ? CollisionSide::Bottom : CollisionSide::Top;
    }
  }

  static bool isInside(const SDL_FRect &a, const SDL_FRect &b) {
    return a.x >= b.x && a.y >= b.y && a.x + a.w <= b.x + b.w &&
           a.y + a.h <= b.y + b.h;
  }

  static CollisionSide AABB_Inside(const SDL_FRect &a, const SDL_FRect &b) {
    if (!isInside(a, b))
      return CollisionSide::None;

    float left = a.x - b.x;
    float right = (b.x + b.w) - (a.x + a.w);
    float top = a.y - b.y;
    float bottom = (b.y + b.h) - (a.y + a.h);

    float minDist = left;
    CollisionSide side = CollisionSide::Left;

    if (right < minDist) {
      minDist = right;
      side = CollisionSide::Right;
    }
    if (top < minDist) {
      minDist = top;
      side = CollisionSide::Top;
    }
    if (bottom < minDist) {
      minDist = bottom;
      side = CollisionSide::Bottom;
    }

    return side;
  }

  static CollisionSide screenCollision(const SDL_FRect &obj, float w, float h) {
    if (obj.x <= 0.0f)
      return CollisionSide::Left;
    if (obj.x + obj.w >= w)
      return CollisionSide::Right;
    if (obj.y <= 0.0f)
      return CollisionSide::Top;
    if (obj.y + obj.h >= h)
      return CollisionSide::Bottom;
    return CollisionSide::None;
  }

  static double dist2points(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
  }
};

} // namespace tebya