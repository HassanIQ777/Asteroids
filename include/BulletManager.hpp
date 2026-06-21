#pragma once

#include "Bullet.hpp"
#include "Player.hpp"

namespace Asteroids {

class BulletManager {
  std::vector<std::unique_ptr<Bullet>> bullets;
  tebya::Texture *bullet_texture;

public:
  BulletManager() {}
  void update(Player &player);
  void render();
  // void handleCollisions

  void spawn(Player &player, tebya::Texture *tex);
  size_t size() const;
  bool empty() const;
  void clear();
  std::vector<std::unique_ptr<Bullet>> &getBullets() { return bullets; }
}; // end of class BulletManager

} // namespace Asteroids