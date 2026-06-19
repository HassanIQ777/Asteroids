#pragma once

#include "Globals.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <stdexcept>

namespace tebya {

inline void init(Globals &globals) {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // 0 is success
  {
    SDL_Log("SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    SDL_Log("IMG_Init failed: %s\n", IMG_GetError());
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    throw std::runtime_error("Failed to initialize SDL_ttf: " +
                             std::string(TTF_GetError()));
  }

  // Initialize SDL_mixer audio
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw std::runtime_error("Failed to initialize SDL_mixer: " +
                             std::string(Mix_GetError()));
  }

  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
    SDL_Log("Warning: Failed to initialize SDL_mixer for MP3/OGG: %s",
            Mix_GetError());
  }

  globals.window =
      SDL_CreateWindow(globals.window_name.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, globals.width, globals.height,
                       SDL_WINDOW_RESIZABLE);

  globals.renderer.r = SDL_CreateRenderer(globals.window, 0, 0);
  SDL_SetWindowResizable(globals.window, SDL_TRUE);
  SDL_SetRenderDrawBlendMode(globals.renderer.r, SDL_BLENDMODE_BLEND);
}

inline void quit(Globals &globals) {
  SDL_DestroyWindow(globals.window);
  SDL_DestroyRenderer(globals.renderer.r);

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
  SDL_Log("SDL quit successfully!\n");
}

} // namespace tebya