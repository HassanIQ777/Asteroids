#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <cstddef>
#include <memory>
#include <unordered_map>

#include "Texture.hpp"

namespace tebya {

class TextureManager {
  std::unordered_map<size_t, std::unique_ptr<Texture>> textures;
  // id - Texture

public:
  TextureManager() = default;

  void addTexture(std::unique_ptr<Texture> texture);
  void addTexture(Texture texture);

  Texture *getTexture(size_t id);
  const Texture *getTexture(size_t id) const;

  bool removeTexture(size_t id);
};

} // namespace tebya