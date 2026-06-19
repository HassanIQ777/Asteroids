#pragma once

#include "Tebya/Texture.hpp"
#include <SDL2/SDL_rect.h>

namespace Asteroids {

class GameObject {
protected:
  SDL_FRect hitbox;
  tebya::Texture *texture;
  bool isAlive = true;
  float angle;
  float speed;
}; // end of class GameObject

} // namespace Asteroids