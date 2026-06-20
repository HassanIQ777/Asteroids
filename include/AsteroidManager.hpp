#pragma once

#include "Asteroid.hpp"
#include "Player.hpp"
#include "Tebya/Globals.hpp"
#include "Tebya/Texture.hpp"
#include <cstddef>
#include <memory>
#include <vector>

namespace Asteroids {

class AsteroidManager {
  std::vector<std::unique_ptr<Asteroid>> asteroids;
  tebya::Texture *asteroid_texture;

public:
  AsteroidManager();
  void update(tebya::Globals &g, Player &player);
  void render(tebya::Globals &g);
  void onHit(Asteroid *a);
  bool checkCollision(SDL_FRect other); // for bullets/player to query (and also
                                        // other asteroids)
  void spawnWave(int count, tebya::Texture *tex);
  size_t size() const;
  bool empty() const;

}; // end of class AsteroidManager

} // namespace Asteroids