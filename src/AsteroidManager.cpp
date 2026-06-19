#include "../include/AsteroidManager.hpp"
#include "Asteroid.hpp"
#include "Tebya/Globals.hpp"
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <cstddef>

namespace Asteroids {

AsteroidManager::AsteroidManager() {
  // implement later
}

void AsteroidManager::update(tebya::Globals &g) {
  if (empty()) // for some reason if we don't do this it seg faults. Hmmmmm....
    return;
  for (auto &a : asteroids) {
    a->update();
  }

  // erase after we finished updating
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [](const auto &a) { return !a->isAlive(); }),
                  asteroids.end());
}

void AsteroidManager::render(tebya::Globals &g) {
  if (empty()) // for some reason if we don't do this it seg faults :D
    return;
  for (auto &a : asteroids) {
    a->render();
  }
}

void AsteroidManager::onHit(Asteroid *a) {
  if (a->size_modifier > 1) {
    for (int i = 0; i < 2; i++) {
      asteroids.push_back(
          Asteroid::create(a->getHitbox(), a->getSpeed(), asteroid_texture));
    }
  }
  a->kill();
}

void AsteroidManager::spawnWave(int count, tebya::Texture *tex) {
  asteroid_texture = tex; // set it here, or in constructor
  tebya::Globals &g = tebya::Globals::getInstance();
  SDL_FRect screen{0, 0, (float)g.width, (float)g.height};

  // Spawn strictly outside by picking an edge instead of rejection sampling
  while (count > 0) {
    float x, y;
    int edge = Random::getint(0, 3);
    float margin = 60.0f;

    switch (edge) {
    case 0:
      x = Random::getdouble(0, g.width);
      y = -margin;
      break; // top
    case 1:
      x = Random::getdouble(0, g.width);
      y = g.height + margin;
      break; // bottom
    case 2:
      x = -margin;
      y = Random::getdouble(0, g.height);
      break; // left
    case 3:
      x = g.width + margin;
      y = Random::getdouble(0, g.height);
      break; // right
    }

    float size = Random::getdouble(50, 200);
    SDL_FRect hitbox = {x, y, size, size};
    float speed = Random::getdouble(30, 150); // pixels/sec, not 0.5–3

    asteroids.push_back(Asteroid::create(hitbox, speed, asteroid_texture));
    count--;
  }
}

bool AsteroidManager::empty() const { return asteroids.empty(); }

size_t AsteroidManager::size() const { return asteroids.size(); }

} // namespace Asteroids