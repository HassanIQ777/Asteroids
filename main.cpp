#include "AsteroidManager.hpp"
#include "Math.hpp"
#include "Player.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Texture.hpp"
#include "Tebya/TextureManager.hpp"
#include "TebyaEngine/Tebya.hpp"
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <memory>
#include <string>

using namespace tebya;

int main() {
  Globals &g = Globals::getInstance();

  g.window_name = "Asteroids";
  tebya::setScreenDimensions(1000, 800);
  init(g);

  // Game vars
  TextureManager tm;
  tm.addTexture(std::make_unique<Texture>(g, "assets/Asteroid.png", 0));
  tm.addTexture(std::make_unique<Texture>(g, "assets/Kla'ed.png", 1));

  Asteroids::AsteroidManager asteroid_manager;
  asteroid_manager.spawnWave(20, tm.getTexture(0));

  Asteroids::Player player{{(float)g.width / 2, (float)g.height / 2, 100, 100},
                           tm.getTexture(1)};
  SDL_FRect player_hitbox = player.getHitbox();
  g.camera.x =
      (float)g.width * 0.5f - (player_hitbox.x + player_hitbox.w * 0.5f);
  g.camera.y =
      (float)g.height * 0.5f - (player_hitbox.y + player_hitbox.h * 0.5f);

  Text text_info{g, "assets/Xirod.otf", 30};
  //

  while (g.running) {
    update();
    g.renderer.clear(Colors::GameBlack);

    // --- logic ---
    float dt = g.delta_time.deltaTime();
    if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
      g.running = false;
    }
    player.update();
    player.handleMovement(g);

    asteroid_manager.update(g, player);
    if (static Timer t; asteroid_manager.size() < 100 && t.elapsed() > 1) {
      asteroid_manager.spawnWave(10, tm.getTexture(0));
      t.restart();
    }
    player_hitbox = player.getHitbox();
    float target_camera_x =
        (float)g.width * 0.5f - (player_hitbox.x + player_hitbox.w * 0.5f);
    float target_camera_y =
        (float)g.height * 0.5f - (player_hitbox.y + player_hitbox.h * 0.5f);
    float camera_follow = std::min(dt * 8.0f, 1.0f);
    g.camera.x = Asteroids::lerp(g.camera.x, target_camera_x, camera_follow);
    g.camera.y = Asteroids::lerp(g.camera.y, target_camera_y, camera_follow);

    // --- draw ---
    player.render();
    asteroid_manager.render(g);
    text_info.render("Asteroids: " + std::to_string(asteroid_manager.size()), 5,
                     5, Colors::Amethyst);

    present();
  }

  quit(g);
  return 0;
}
