#include "../include/Entities.hpp"
#include <SDL2/SDL_rect.h>

namespace Asteroids {

void Entities::handleCollisions() {
  for (auto &asteroid : asteroid_manager.getAsteroids()) {
    for (auto &bullet : bullet_manager.getBullets()) {
      if (SDL_HasIntersectionF(&asteroid->getHitbox(), &bullet->getHitbox())) {
        asteroid->takeDamage(bullet->getDamage());
        bullet->kill();
      }
    }

    if(SDL_HasIntersectionF(&asteroid->getHitbox(), &player.getHitbox())){
        
    }
  }
}

} // namespace Asteroids