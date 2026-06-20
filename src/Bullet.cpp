#include "../include/Bullet.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Globals.hpp"

namespace Asteroids {

void Bullet::render() {
  if (!texture)
    return;

  tebya::Globals &g = tebya::Globals::getInstance();
  SDL_FRect render_pos = {hitbox.x + g.camera.x, hitbox.y + g.camera.y,
                          hitbox.w, hitbox.h};

  SDL_Rect bullet_source = {21, 21, 84, 81};
  texture->render(g, bullet_source, render_pos, angle);

#ifdef DEBUG
  g.renderer.drawRectF(render_pos, tebya::Colors::DebugGreen);
#endif
}

} // namespace Asteroids
