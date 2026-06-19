#pragma once

#include "Asteroid.hpp"
#include "Tebya/Globals.hpp"
#include "Tebya/Texture.hpp"
#include <memory>
#include <vector>

namespace Asteroids {

class AsteroidManager {
  std::vector<std::unique_ptr<Asteroid>> asteroids;
  tebya::Texture *asteroid_texture;

public:
  AsteroidManager();
  void update(tebya::Globals &g);
  void render(tebya::Globals &g);
  void onHit(Asteroid *a);
  bool checkCollision(SDL_FRect other); // for bullets/player to query (and also
                                        // other asteroids)
  bool empty();

}; // end of class AsteroidManager

} // namespace Asteroids