// DamageFlash.hpp
#pragma once
#include "Tebya/Globals.hpp"
#include <SDL2/SDL_render.h>

namespace Asteroids {

class DamageFlash {
  float alpha = 0.0f;    // current opacity — 0 = invisible, 255 = YOU'RE DEAD
  float duration = 0.3f; // seconds until fully faded
  float timer = 0.0f;    // counts down

  // tweak these to taste
  static constexpr float PEAK_ALPHA = 180.0f;
  static constexpr float DECAY = PEAK_ALPHA / 1.0f; // alpha units per second

public:
  void trigger() {
    alpha = PEAK_ALPHA; // PAIN
    timer = duration;
  }

  void update(float dt) {
    if (alpha <= 0.0f)
      return;
    alpha -= DECAY * dt;
    if (alpha < 0.0f)
      alpha = 0.0f;
  }

  void render(tebya::Globals &g) {
    if (alpha <= 0.0f)
      return;

    SDL_SetRenderDrawBlendMode(g.renderer.r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(g.renderer.r, 255, 0, 0, (Uint8)alpha);

    // fullscreen rect — the whole screen bleeds
    SDL_FRect screen{0, 0, (float)g.width, (float)g.height};
    SDL_RenderFillRectF(g.renderer.r, &screen);
  }

  bool isActive() const { return alpha > 0.0f; }
};

} // namespace Asteroids