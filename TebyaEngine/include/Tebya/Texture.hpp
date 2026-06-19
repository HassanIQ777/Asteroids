#pragma once

#include "Globals.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <string>
#include <sys/types.h>

namespace tebya {

class Texture {
  SDL_Texture *texture;
  size_t id;
  SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
  Texture(Globals &globals, const std::string &texture_path, size_t id_);

  ~Texture();

  SDL_Texture *getTexture();

  size_t getId() const;

  // Copies the texture
  void render(Globals &globals, const SDL_FRect &dest) const;
  // Copies the texture with a rotation of angle radians
  void render(Globals &globals, const SDL_FRect &dest, float angle) const;
  void setFlip(SDL_RendererFlip flip);
};

} // namespace tebya