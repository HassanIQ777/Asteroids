#pragma once

#include "GameObject.hpp"
#include "Math.hpp"
#include "Tebya/Globals.hpp"
#include "Tebya/Texture.hpp"

namespace Asteroids {

class Player : public GameObject {
  bool hasInvincibility = false;

public:
  Player(SDL_FRect hitbox_, tebya::Texture *tex) {
    hitbox = hitbox_;
    texture = tex;
    hp = 3;
    angle = degreeToRad(90);
    type = GameObjectType::Player;
  }
  Player() {
    hp = 3;
    angle = degreeToRad(90);
    type = GameObjectType::Player;
  }

  void init(SDL_FRect hitbox_, tebya::Texture *tex) {
    hitbox = hitbox_;
    texture = tex;
  }

  void render() override;
  void takeDamage();
  void handleMovement(tebya::Globals &g);
  void revive() {
    hp = 3;
    alive = true;
  }
  void renderHearts(tebya::Globals &g, tebya::Texture *tex);
}; // end of class Player

} // namespace Asteroids