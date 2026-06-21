#include "../include/Player.hpp"
#include "../libutils/src/Timer.hpp"
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

  SDL_Rect player_source = {28, 13, 72, 88};
  texture->render(g, player_source, render_pos, angle + degreeToRad(90.0f));

#ifdef DEBUG
  g.renderer.drawRectF(render_pos, tebya::Colors::DebugGreen);
#endif
}

void Player::takeDamage() {

  if (hasInvincibility) {
    static Timer t;
    if (t.elapsed() > 3.0f) {
      hasInvincibility = false;
      t.restart();
    }
    return; // don't take damage
  }

  if (!hasInvincibility) {
    hasInvincibility = true;
    hp -= 1;
    if (hp < 0) {
      alive = false;
      hp = 0;
      return;
    }
  }
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
