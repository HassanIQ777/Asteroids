#pragma once

#include "GameObject.hpp"
#include <memory>

namespace Asteroids {

class Bullet : public GameObject {
  float damage;

public:
  Bullet(SDL_FRect hitbox_, float speed_, tebya::Texture *tex, float angle_) {
    hitbox = hitbox_;
    speed = speed_;
    texture = tex;
    angle = angle_;
    move_angle = angle;
    damage = 5;
    type = GameObjectType::Bullet;
  }

  void render() override;

  static std::unique_ptr<Bullet> create(SDL_FRect hitbox, float speed,
                                        tebya::Texture *tex, float angle) {
    return std::make_unique<Bullet>(hitbox, speed, tex, angle);
  }

  float getDamage() const { return damage; }

}; // end of class Bullet

} // namespace Asteroids
