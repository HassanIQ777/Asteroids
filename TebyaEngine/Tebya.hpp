#pragma once

// this is the master include for Tebya Engine

#include "Tebya/Audio.hpp"
#include "Tebya/AudioGenerator.hpp"
#include "Tebya/Button.hpp"
#include "Tebya/Collision.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/DeltaTime.hpp"
#include "Tebya/FPSCounter.hpp"
#include "Tebya/Globals.hpp"
#include "Tebya/Input.hpp"
#include "Tebya/MicRecorder.hpp"
#include "Tebya/Renderer.hpp"
#include "Tebya/Text.hpp"
#include "Tebya/Texture.hpp"
#include "Tebya/TextureManager.hpp"
#include "Tebya/Timer.hpp"
#include "Tebya/Widget.hpp"
#include "Tebya/init.hpp"
#include "Tebya/screenshot.hpp"

namespace tebya {

inline void setScreenDimensions(int w, int h) {
  Globals &globals = Globals::getInstance();
  globals.width = w;
  globals.height = h;
}

inline void update() {
  Globals &globals = Globals::getInstance();
  globals.delta_time.update();
  globals.fps_counter.update(globals.delta_time.deltaTime());
  globals.input.update(globals.e);
  while (SDL_PollEvent(&globals.e)) {
    switch (globals.e.type) {
    case SDL_QUIT:
      globals.running = false;
      break;
    }
  }
}

inline void present() {
  Globals &globals = Globals::getInstance();
  globals.renderer.present();
  SDL_GetRendererOutputSize(globals.renderer.r, &globals.width,
                            &globals.height);
  globals.delta_time.capFPS();
}

inline float degreeToRad(float angle_degree) {
  return angle_degree * M_PI / 180.0f;
}

inline float radToDegree(float angle_rad) { return angle_rad * 180.0f / M_PI; }

} // namespace tebya