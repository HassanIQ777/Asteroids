#include "BulletManager.hpp"
#include "Bullet.hpp"
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <cmath>

namespace Asteroids {

void BulletManager::update(tebya::Globals &g, Player &player) {
  if (empty())
    return;

  for (std::unique_ptr<Bullet> &b : bullets) {
    if (dist2rects_sq(b->getHitbox(), player.getHitbox()) > 2500.0f * 2500.0f) {
      b->kill();
    }
    b->update();
  }

  // erase after we finished updating
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](const auto &a) { return !a->isAlive(); }),
                bullets.end());
}

void BulletManager::render(tebya::Globals &g) {
  if (empty())
    return;
  for (auto &a : bullets) {
    a->render();
  }
}

void BulletManager::spawn(Player &player, tebya::Texture *tex) {
  SDL_FRect p = player.getHitbox();
  float angle = player.getAngle();

  float bullet_size = 30.0f;
  float nose_distance = p.w * 0.5f;

  SDL_FRect spawn_hitbox = {
      p.x + p.w * 0.5f + std::cos(angle) * nose_distance - bullet_size * 0.5f,
      p.y + p.h * 0.5f + std::sin(angle) * nose_distance - bullet_size * 0.5f,
      bullet_size, bullet_size};

  bullets.push_back(Bullet::create(spawn_hitbox, 1000, tex, angle));
}

size_t BulletManager::size() const { return bullets.size(); }
bool BulletManager::empty() const { return bullets.empty(); }
void BulletManager::clear() { bullets.clear(); }

} // namespace Asteroids
