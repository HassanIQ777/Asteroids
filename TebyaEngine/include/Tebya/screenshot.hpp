#pragma once

#include "Tebya/Globals.hpp"
namespace tebya {

#pragma once

#include <SDL2/SDL.h>
#include <time.h>

// Save the current SDL renderer to a PNG file \n
// auto adds the file extension
inline bool saveScreenshot(int width, int height) {
  SDL_Renderer *renderer = Globals::getInstance().renderer.r;
  // Create a surface from the renderer
  SDL_Surface *surface = SDL_CreateRGBSurface(
      0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

  if (!surface) {
    printf("ERROR: Failed to create surface for screenshot\n");
    return false;
  }

  // Read pixels from renderer into surface
  if (SDL_RenderReadPixels(renderer, nullptr, surface->format->format,
                           surface->pixels, surface->pitch) != 0) {
    printf("ERROR: Failed to read pixels from renderer\n");
    SDL_FreeSurface(surface);
    return false;
  }

  // Generate filename with timestamp
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  char filename[256];
  strftime(filename, sizeof(filename),
           "screenshots/screenshot_%Y%m%d_%H%M%S.bmp", timeinfo);

  // Save as BMP (SDL native format, very fast)
  if (SDL_SaveBMP(surface, filename) != 0) {
    printf("ERROR: Failed to save screenshot: %s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    return false;
  }

  printf("Screenshot saved as: %s\n", filename);
  SDL_FreeSurface(surface);
  return true;
}

} // namespace tebya