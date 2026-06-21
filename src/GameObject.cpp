#include "../include/GameObject.hpp"
#include "Tebya/Colors.hpp"
#include <SDL2/SDL_rect.h>
#include <cmath>

namespace Asteroids {

void GameObject::update() {
  tebya::Globals &g = tebya::Globals::getInstance();
  float dt = g.delta_time.deltaTime();

  hitbox.x += cos(move_angle) * speed * dt;
  hitbox.y += sin(move_angle) * speed * dt;
  angle += rotation_speed * dt;
}

void GameObject::render() {
  if (!texture)
    return;

  tebya::Globals &g = tebya::Globals::getInstance();
  SDL_FRect render_pos = {hitbox.x + g.camera.x, hitbox.y + g.camera.y,
                          hitbox.w, hitbox.h};
  texture->render(g, render_pos, angle);

#ifdef DEBUG
  g.renderer.drawRectF(render_pos, tebya::Colors::DebugGreen);
#endif
}

void GameObject::kill() { alive = false; }
bool GameObject::isAlive() const { return alive; }

void GameObject::takeDamage(float amount) {
  hp -= amount;
  if (hp <= 0) {
    hp = 0;
    alive = false;
  }
}

} // namespace Asteroids
