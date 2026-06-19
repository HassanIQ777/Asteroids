#pragma once

#include "../libutils/src/Random.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL_rect.h>
namespace Asteroids {

class Asteroid : public GameObject {
  int size_modifier;

  Asteroid(SDL_FRect hitbox_, float speed_, tebya::Texture* tex) {
    hitbox         = hitbox_;
    speed          = speed_;
    texture        = tex;
    angle          = (float)Random::getdouble(0, 2 * M_PI); // random direction
    rotation_speed = (float)Random::getdouble(-2, 2);       // can spin either way
    size_modifier  = Random::getint(1, 5);
  }

public:
  static Asteroid* create(SDL_FRect hitbox, float speed, tebya::Texture* tex) {
    return new Asteroid(hitbox, speed, tex);
  }
}; // end of class Asteroid


} // namespace Asteroids