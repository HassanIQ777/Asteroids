#pragma once

#include "AsteroidManager.hpp"
#include "BulletManager.hpp"
#include "Player.hpp"

namespace Asteroids {

struct Entities {
    AsteroidManager asteroid_manager;
    BulletManager bullet_manager;
    Player player;
};

} // namespace Asteroids