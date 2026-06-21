#pragma once

#include "Tebya/Texture.hpp"
#include <SDL2/SDL_rect.h>

namespace Asteroids {

enum class GameObjectType { Player, Asteroid, Bullet };

class GameObject {
protected:
  SDL_FRect hitbox;
  tebya::Texture *texture; // this is owned by TextureManager
  bool alive = true;
  float angle = 0, move_angle = 0; // in radians
  float speed = 0;
  float rotation_speed = 0;
  float hp = 0;
  GameObjectType type;

public:
  virtual void update();
  virtual void render();
  void kill();
  bool isAlive() const;
  virtual void takeDamage(float amount);

  virtual ~GameObject() = default;

  // setters and getters
  const SDL_FRect &getHitbox() const { return hitbox; }
  float getSpeed() const { return speed; }
  GameObjectType getType() const { return type; }
  float getAngle() const { return angle; }

  void setPosition(float x, float y) {
    hitbox.x = x;
    hitbox.y = y;
  }
}; // end of class GameObject

} // namespace Asteroids