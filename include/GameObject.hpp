#pragma once

#include "Tebya/Texture.hpp"
#include <SDL2/SDL_rect.h>

namespace Asteroids {

class GameObject {
protected:
  SDL_FRect hitbox;
  tebya::Texture *texture; // this is owned by TextureManager
  bool alive = true;
  float angle = 0, move_angle = 0; // in radians
  float speed = 1;
  float rotation_speed = 0;
  float hp = 0;

public:
  virtual void update();
  virtual void render();
  virtual void kill();
  virtual bool isAlive() const;
  virtual void takeDamage(float amount);

  virtual ~GameObject() = default;

  // setters and getters
  SDL_FRect getHitbox() const { return hitbox; }
  float getSpeed() const { return speed; }

}; // end of class GameObject

} // namespace Asteroids