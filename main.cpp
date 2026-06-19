#include "TebyaEngine/Tebya.hpp"

using namespace tebya;

int main() {
  Globals &g = Globals::getInstance();
  g.window_name = "Asteroids";
  tebya::setScreenDimensions(1000, 800);
  init(g);

  while (g.running) {
    update();
    g.renderer.clear(Colors::Abyss);

    // --- logic ---
    if (g.input.isKeyJustPressed(KeyCode::ESCAPE)) {
      g.running = false;
    }

    // --- draw ---

    present();
  }

  quit(g);
  return 0;
}
