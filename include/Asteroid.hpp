#pragma once

#include "../libutils/src/Random.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL_rect.h>
#include <memory>
namespace Asteroids {

class Asteroid : public GameObject {

public:
  Asteroid(SDL_FRect hitbox_, float speed_, tebya::Texture *tex) {
    hitbox = hitbox_;
    speed = speed_;
    texture = tex;
    angle = (float)Random::getdouble(0, 2 * M_PI); // random direction
    move_angle = angle;
    rotation_speed = (float)Random::getdouble(-2, 2); // can spin either way
    size_modifier = (float)Random::getdouble(1, 3);
    hp = Random::getdouble(1, 3) * size_modifier; // larger = harder to destroy
    type = GameObjectType::Asteroid;
  }

public:
  void render() override;

  static std::unique_ptr<Asteroid> create(SDL_FRect hitbox, float speed,
                                          tebya::Texture *tex) {
    return std::make_unique<Asteroid>(hitbox, speed, tex);
  }

  float size_modifier;
}; // end of class Asteroid

} // namespace Asteroids
