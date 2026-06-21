#include "Entities.hpp"
#include "Math.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Input.hpp"
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
  tm.addTexture(std::make_unique<Texture>(g, "assets/03.png", 2));

  Asteroids::Entities entities;

  entities.asteroid_manager.spawnWave(20, tm.getTexture(0));

  entities.player.init({(float)g.width / 2, (float)g.height / 2, 65, 65},
                       tm.getTexture(1));
  SDL_FRect player_hitbox = entities.player.getHitbox();
  g.camera.x =
      (float)g.width * 0.5f - (player_hitbox.x + player_hitbox.w * 0.5f);
  g.camera.y =
      (float)g.height * 0.5f - (player_hitbox.y + player_hitbox.h * 0.5f);

  Text text_info{g, "assets/Xirod.otf", 20};
  //

  while (g.running) {
    update();
    g.renderer.clear(Colors::GameBlack);

    // --- logic ---
    float dt = g.delta_time.deltaTime();
    if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
      g.running = false;
    }
    entities.player.update();
    entities.player.handleMovement(g);

    entities.asteroid_manager.update(g, entities.player);
    if (static Timer t;
        entities.asteroid_manager.size() < 100 && t.elapsed() > .1) {
      entities.asteroid_manager.spawnWave(1, tm.getTexture(0));
      t.restart();
    }
    if (g.input.isKeyPressed(KeyCode::SPACE)) {
      if (static Timer t{1}; t.elapsed() > .2f) {
        entities.bullet_manager.spawn(entities.player, tm.getTexture(2));
        t.restart();
      }
    }

    player_hitbox = entities.player.getHitbox();
    float target_camera_x =
        (float)g.width * 0.5f - (player_hitbox.x + player_hitbox.w * 0.5f);
    float target_camera_y =
        (float)g.height * 0.5f - (player_hitbox.y + player_hitbox.h * 0.5f);
    float camera_follow = std::min(dt * 8.0f, 1.0f);
    g.camera.x = Asteroids::lerp(g.camera.x, target_camera_x, camera_follow);
    g.camera.y = Asteroids::lerp(g.camera.y, target_camera_y, camera_follow);

    entities.bullet_manager.update(g, entities.player);
    entities.handleCollisions();

    // --- draw ---
    entities.player.render();
    entities.bullet_manager.render(g);
    entities.asteroid_manager.render(g);
    text_info.render("Asteroids: " +
                         std::to_string(entities.asteroid_manager.size()),
                     5, 5, Colors::Amethyst);
    text_info.render("Bullets: " +
                         std::to_string(entities.bullet_manager.size()),
                     5, 50, Colors::Amethyst);

    text_info.render("HP: " + std::to_string((int)entities.player.getHP()), 5,
                     100, Colors::Amethyst);

    text_info.render("Asteroids", g.width / 2, 5, Colors::DeepPink, true);

    present();
  }

  entities.asteroid_manager.clear();
  entities.bullet_manager.clear();

  quit(g);
  return 0;
}
