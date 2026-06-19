#include "AsteroidManager.hpp"
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

  Asteroids::AsteroidManager asteroid_manager;
  asteroid_manager.spawnWave(100, tm.getTexture(0));
  //

  while (g.running) {
    update();
    g.renderer.clear(Colors::GameBlack);

    // --- logic ---
    if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
      g.running = false;
    }
    asteroid_manager.update(g);
    if (asteroid_manager.size() < 50) {
      asteroid_manager.spawnWave(10, tm.getTexture(0));
    }

    // --- draw ---
    asteroid_manager.render(g);

    present();
  }

  quit(g);
  return 0;
}
