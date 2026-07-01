#include "Math.hpp"
#include "Tebya/Audio.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Input.hpp"
#include "Tebya/Texture.hpp"
#include "Tebya/TextureManager.hpp"
#include "TebyaEngine/Tebya.hpp"
#include "scenes.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <algorithm>
#include <cmath>
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
  tm.addTexture(std::make_unique<Texture>(g, "assets/heart.png", 3));

  Asteroids::Entities e;

  e.asteroid_manager.spawnWave(20, tm.getTexture(0));

  e.player.init({(float)g.width / 2, (float)g.height / 2, 65, 65},
                tm.getTexture(1));
  SDL_FRect player_hitbox = e.player.getHitbox();
  g.camera.x =
      (float)g.width * 0.5f - (player_hitbox.x + player_hitbox.w * 0.5f);
  g.camera.y =
      (float)g.height * 0.5f - (player_hitbox.y + player_hitbox.h * 0.5f);

  Text text_title{g, "assets/Xirod.otf", 30};
  Text text_info{g, "assets/Xirod.otf", 20};
  Text text_button{g, "assets/Xirod.otf", 25};

  Asteroids::UI_State ui_state = Asteroids::UI_State::StartMenu;
  Scene start_menu;
  Asteroids::initStartMenu(g, start_menu, text_button, ui_state);
  Scene death_menu;
  Asteroids::initDeathMenu(g, death_menu, text_button, ui_state, e);
  bool paused = false;
  //

  while (g.running) {
    update();
    // --- logic ---
    float dt = g.delta_time.deltaTime();

    switch (ui_state) {
    case Asteroids::UI_State::StartMenu:
      g.renderer.clear(Colors::Black);
      start_menu.update();
      start_menu.render();
      if (g.input.isKeyJustPressed(KeyCode::SPACE)) {
        ui_state = Asteroids::UI_State::Playing;
      }
      break;

    case Asteroids::UI_State::DeathMenu:
      g.renderer.clear(Colors::ShadowBlack);
      text_title.render("You Died!", g.width / 2,
                        static_cast<float>(g.height) * .75 / 2 - 75,
                        Colors::DamageRed, true);
      death_menu.update();
      death_menu.render();
      if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
        g.running = false;
      }
      break;

    case Asteroids::UI_State::Playing:
      if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
        paused = !paused;
      }
      if (!paused) {

        e.player.update();
        e.player.handleMovement(g);

        e.asteroid_manager.update(e.player);
        if (static Timer t;
            e.asteroid_manager.size() < 50 && t.elapsed() > .1) {
          e.asteroid_manager.spawnWave(1, tm.getTexture(0));
          t.restart();
        }
        if (g.input.isKeyPressed(KeyCode::SPACE)) {
          if (static Timer t{1}; t.elapsed() > .2f) {
            e.bullet_manager.spawn(e.player, tm.getTexture(2));
            // play audio
            static Audio audio_shoot_bullet{"assets/shoot.wav"};
            audio_shoot_bullet.setVolume(50);
            audio_shoot_bullet.play();
            t.restart();
          }
        }

        player_hitbox = e.player.getHitbox();
        float target_camera_x =
            (float)g.width * 0.5f - (player_hitbox.x + player_hitbox.w * 0.5f);
        float target_camera_y =
            (float)g.height * 0.5f - (player_hitbox.y + player_hitbox.h * 0.5f);
        float camera_follow = std::min(dt * 8.0f, 1.0f);
        g.camera.x = Asteroids::lerp(g.camera.x, target_camera_x,
                                     1 - std::exp(-camera_follow));
        g.camera.y = Asteroids::lerp(g.camera.y, target_camera_y,
                                     1 - std::exp(-camera_follow));

        e.bullet_manager.update(e.player);
        e.handleCollisions();
        e.player.damage_flash.update(dt);
      }
      // --- draw ---
      g.renderer.clear(Colors::GameBlack);
      e.player.render();
      e.bullet_manager.render();
      e.asteroid_manager.render();
      e.player.renderHearts(g, tm.getTexture(3));

      if (e.player.getHP() == 0) {
        ui_state = Asteroids::UI_State::DeathMenu;
      }
      e.player.damage_flash.render(g);

      break;
    }

    text_title.render("Asteroids", g.width / 2, 5, Colors::DeepPink, true);
    if (paused) {
      text_info.render("Paused", g.width / 2, 50, Colors::MediumVioletRed,
                       true);
    }

    present();
  }

  e.asteroid_manager.clear();
  e.bullet_manager.clear();

  text_info.clear();
  text_title.clear();
  text_button.clear();

  quit(g);
  return 0;
}
