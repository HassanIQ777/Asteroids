#pragma once

#include "GameObject.hpp"
#include "Math.hpp"
#include "Tebya/Globals.hpp"

namespace Asteroids {

class Player : public GameObject {
public:
  Player(SDL_FRect hitbox_, tebya::Texture *tex) {
    hitbox = hitbox_;
    texture = tex;
    hp = 3;
    angle = degreeToRad(0);
  }

  void render() override;
  void handleMovement(tebya::Globals &g);
}; // end of class Player

} // namespace Asteroids