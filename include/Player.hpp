#pragma once

#include "GameObject.hpp"

namespace Asteroids {

class Player : public GameObject {
    void handleMovement();
}; // end of class Player

} // namespace Asteroids