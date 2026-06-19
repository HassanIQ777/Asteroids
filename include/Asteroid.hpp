#pragma once

#include "GameObject.hpp"
#include <SDL2/SDL_rect.h>
namespace Asteroids {

class Asteroid : public GameObject {
  int size_modifier = 1; 
};

} // namespace Asteroids