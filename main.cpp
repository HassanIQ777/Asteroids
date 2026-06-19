#include "TebyaEngine/Tebya.hpp"

using namespace tebya;

int main() {
    Globals &g = Globals::getInstance();
    g.window_name = "Asteroids";
    tebya::setScreenDimensions(800, 600);
    init(g);

    while (g.running) {
        update();
        g.renderer.clear(Colors::Abyss);

        // --- logic ---

        // --- draw ---

        present();
    }

    quit(g);
    return 0;
}
