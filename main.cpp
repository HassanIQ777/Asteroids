#include "AsteroidManager.hpp"
#include "Player.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Texture.hpp"
#include "Tebya/TextureManager.hpp"
#include "TebyaEngine/Tebya.hpp"
#include <memory>

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
  asteroid_manager.spawnWave(100, tm.getTexture(0));

  Asteroids::Player player{{(float)g.width / 2, (float)g.height / 2, 100, 100},
                           tm.getTexture(1)};
  //

  while (g.running) {
    update();
    g.renderer.clear(Colors::GameBlack);

    // --- logic ---
    if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
      g.running = false;
    }
    player.update();
    player.handleMovement(g);

    asteroid_manager.update(g, player);
    if (asteroid_manager.size() < 50) {
      asteroid_manager.spawnWave(10, tm.getTexture(0));
    }

    // --- draw ---
    player.render();
    asteroid_manager.render(g);

    present();
  }

  quit(g);
  return 0;
}
