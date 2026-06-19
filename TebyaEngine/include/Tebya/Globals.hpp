#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

#include "DeltaTime.hpp"
#include "Renderer.hpp"
#include "Tebya/FPSCounter.hpp"
#include "Tebya/Input.hpp"

namespace tebya {

struct Globals {
  Renderer renderer;
  SDL_Window *window;
  int width, height;
  SDL_Event e;
  bool running = true;
  std::string window_name;
  DeltaTime delta_time;
  FPSCounter fps_counter;
  InputManager input;
  SDL_FPoint camera = {0.0f, 0.0f}; // camera starts at origin

  static Globals &getInstance() {
    static Globals instance;
    return instance;
  }

  Globals(const Globals &) = delete;
  Globals(Globals &&) = delete;
  Globals &operator=(const Globals &) = delete;
  Globals &operator=(Globals &&) = delete;

private:
  Globals()
      : renderer(nullptr), window(nullptr), width(800), height(600),
        window_name("Tebya Engine") {} // Initialize Renderer with nullptr
};

} // namespace tebya