#include "../include/Player.hpp"
#include "Math.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Input.hpp"
#include <algorithm>

namespace Asteroids {

void Player::render() {
  if (!texture)
    return;

  tebya::Globals &g = tebya::Globals::getInstance();
  SDL_FRect render_pos = {hitbox.x + g.camera.x, hitbox.y + g.camera.y,
                          hitbox.w, hitbox.h};
  texture->render(g, render_pos, angle + degreeToRad(90.0f));

#ifdef DEBUG
  g.renderer.drawRectF(render_pos, tebya::Colors::DebugGreen);
#endif
}

void Player::handleMovement(tebya::Globals &g) {
  float dt = g.delta_time.deltaTime();
  // Propel the player (Add speed)
  if (g.input.isKeyPressed(tebya::KeyCode::UP)) {
    speed += 1500 * dt;
    speed = std::min(speed, 900.0f); // terminal velocity
  }

  if (g.input.isKeyPressed(tebya::KeyCode::DOWN)) {
    speed *= 0.96f;
  }

  // Change angle
  float angle_amount = degreeToRad(180) * dt;
  if (g.input.isKeyPressed(tebya::KeyCode::LEFT))
    move_angle -= angle_amount;

  // Change angle
  if (g.input.isKeyPressed(tebya::KeyCode::RIGHT))
    move_angle += angle_amount;

  angle = move_angle;
  speed *= 0.99f; // friction (i guess...)

  // SHOOT BULLETS
  if (g.input.isKeyPressed(tebya::KeyCode::SPACE)) {
  }
}

} // namespace Asteroids
