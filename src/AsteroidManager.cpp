#include "../include/AsteroidManager.hpp"
#include <algorithm>

namespace Asteroids {
void AsteroidManager::update(tebya::Globals &g) {
  for (auto &a : asteroids) {
    a->update();
  }

  // erase after we finished updating
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [](const auto &a) { return !a->isAlive(); }));
}
} // namespace Asteroids