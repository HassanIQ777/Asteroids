#include "../include/Player.hpp"
#include "Math.hpp"
#include "Tebya/Input.hpp"

namespace Asteroids {

void Player::render() {
  if (!texture)
    return;

  tebya::Globals &g = tebya::Globals::getInstance();
  texture->render(g, hitbox, move_angle);
}

void Player::handleMovement(tebya::Globals &g) {
  float dt = g.delta_time.deltaTime();
  // Propel the player (Add speed)
  if (g.input.isKeyPressed(tebya::KeyCode::SPACE)) {
    speed += 1500 * dt;
    speed = std::min(speed, 600.0f); // terminal velocity
  }

  // Change angle
  float angle_amount = degreeToRad(180) * dt;
  if (g.input.isKeyPressed(tebya::KeyCode::LEFT))
    move_angle -= angle_amount;

  // Change angle
  if (g.input.isKeyPressed(tebya::KeyCode::RIGHT))
    move_angle += angle_amount;

  angle = move_angle;
  speed *= 0.98f; // friction (i guess...)
}

} // namespace Asteroids