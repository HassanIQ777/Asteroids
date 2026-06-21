#include "../include/AsteroidManager.hpp"
#include "Asteroid.hpp"
#include "Math.hpp"
#include "Tebya/Globals.hpp"
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <cstddef>

namespace Asteroids {

AsteroidManager::AsteroidManager() {
  // implement later
}

void AsteroidManager::update(Player &player) {
  if (empty()) // for some reason if we don't do this it seg faults. Hmmmmm....
    return;
  for (std::unique_ptr<Asteroid> &a : asteroids) {
    if (dist2rects_sq(a->getHitbox(), player.getHitbox()) > 2500.0f * 2500.0f) {
      a->kill();
    }
    a->update();
  }

  // erase after we finished updating
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [](const auto &a) { return !a->isAlive(); }),
                  asteroids.end());
}

void AsteroidManager::render() {
  if (empty()) // for some reason if we don't do this it seg faults :D
    return;
  for (auto &a : asteroids) {
    a->render();
  }
}

void AsteroidManager::onHit(std::unique_ptr<Asteroids::Asteroid> &a) {
  if (a->size_modifier > 1) {
    for (int i = 0; i < 2; i++) {
      asteroids.push_back(Asteroid::create(
          a->getHitbox(), a->getSpeed() + Random::getdouble(-50, 50),
          asteroid_texture, std::fmax(1, a->size_modifier - 1)));
    }
  }
  a->kill();
}

void AsteroidManager::spawnWave(int count, tebya::Texture *tex) {
  asteroid_texture = tex; // set it here, or in constructor
  tebya::Globals &g = tebya::Globals::getInstance();
  SDL_FRect viewport{-g.camera.x, -g.camera.y, (float)g.width, (float)g.height};

  // Spawn strictly outside by picking an edge instead of rejection sampling
  while (count > 0) {
    float x, y;
    int edge = Random::getint(0, 3);
    float margin = 300; // this is how far we push each asteroid on spawn (to
                        // prevent it suddenly apprearing on-screen)

    switch (edge) {
    case 0:
      x = Random::getdouble(viewport.x, viewport.x + viewport.w);
      y = viewport.y - margin;
      break; // top
    case 1:
      x = Random::getdouble(viewport.x, viewport.x + viewport.w);
      y = viewport.y + viewport.h + margin;
      break; // bottom
    case 2:
      x = viewport.x - margin;
      y = Random::getdouble(viewport.y, viewport.y + viewport.h);
      break; // left
    case 3:
      x = viewport.x + viewport.w + margin;
      y = Random::getdouble(viewport.y, viewport.y + viewport.h);
      break; // right
    }

    SDL_FPoint coords = {x, y};

    asteroids.push_back(Asteroid::create(coords, asteroid_texture));
    count--;
  }
}

bool AsteroidManager::empty() const { return asteroids.empty(); }

size_t AsteroidManager::size() const { return asteroids.size(); }
void AsteroidManager::clear() { asteroids.clear(); }

} // namespace Asteroids
