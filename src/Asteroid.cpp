#include "../include/Asteroid.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Globals.hpp"

namespace Asteroids {

void Asteroid::render() {
  if (!texture)
    return;

  tebya::Globals &g = tebya::Globals::getInstance();
  SDL_FRect render_pos = {hitbox.x + g.camera.x, hitbox.y + g.camera.y,
                          hitbox.w, hitbox.h};

  // Asteroid.png has a lot of transparent padding. Crop to its opaque pixels so
  // the visible rock matches the gameplay hitbox.
  SDL_Rect asteroid_source = {29, 32, 38, 33};
  texture->render(g, asteroid_source, render_pos, angle);

#ifdef DEBUG
  g.renderer.drawRectF(render_pos, tebya::Colors::DebugGreen);
#endif
}

} // namespace Asteroids
