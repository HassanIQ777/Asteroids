#pragma once

#include "Bullet.hpp"
#include "Player.hpp"

namespace Asteroids {

class BulletManager {
  std::vector<std::unique_ptr<Bullet>> bullets;
  tebya::Texture *bullet_texture;

public:
  BulletManager() {}
  void update(tebya::Globals &g, Player &player);
  void render(tebya::Globals &g);
  // void handleCollisions

  void spawn(Player &player, tebya::Texture *tex);
  size_t size() const;
  bool empty() const;
  void clear();
}; // end of class BulletManager

} // namespace Asteroids