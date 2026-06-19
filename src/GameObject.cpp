#include "../include/GameObject.hpp"
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
  texture->render(g, hitbox, angle);
}

void GameObject::kill() { alive = false; }
bool GameObject::isAlive() const { return alive; }

void GameObject::takeDamage(float amount) {
  hp -= amount;
  if (hp < 0) {
    hp = 0;
    alive = false;
  }
}

} // namespace Asteroids