#include "Tebya/Text.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>

namespace tebya {

Text::Text(Globals &globals_, const std::string &fontPath, int fontSize)
    : globals(globals_), font(TTF_OpenFont(fontPath.c_str(), fontSize)) {
  if (!font) {
    throw std::runtime_error("Failed to load font: " +
                             std::string(TTF_GetError()));
  }
}

Text::~Text() { clear(); }

void Text::render(const std::string &text, int x, int y, SDL_Color color,
                  bool centered) {
  // Cache key includes text AND color to avoid color conflicts
  std::string cacheKey =
      text + "_" + std::to_string(color.r) + "_" + std::to_string(color.g) +
      "_" + std::to_string(color.b) + "_" + std::to_string(color.a);

  // Check if texture is already cached
  if (textureCache.find(cacheKey) == textureCache.end()) {
    // Render text to a surface
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
      throw std::runtime_error("Failed to create text surface: " +
                               std::string(TTF_GetError()));
    }

    // Create a texture from the surface
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(globals.renderer.get(), surface);
    SDL_FreeSurface(surface);
    if (!texture) {
      throw std::runtime_error("Failed to create text texture: " +
                               std::string(SDL_GetError()));
    }

    // Cache the texture
    textureCache[cacheKey] = texture;
  }

  // Get the cached texture
  SDL_Texture *texture = textureCache[cacheKey];

  // Query texture dimensions
  int textWidth, textHeight;
  SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

  // Render the texture to the screen
  SDL_Rect destRect = {x, y, textWidth, textHeight};
  if (centered)
    destRect.x -= textWidth / 2;
  SDL_RenderCopy(globals.renderer.get(), texture, NULL, &destRect);
}

void Text::renderInside(const std::string &text, SDL_FRect bounds,
                        SDL_Color color, bool centered) {
  // Cache key includes text AND color
  std::string cacheKey =
      text + "_" + std::to_string(color.r) + "_" + std::to_string(color.g) +
      "_" + std::to_string(color.b) + "_" + std::to_string(color.a);

  auto it = textureCache.find(cacheKey);
  if (it == textureCache.end()) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
      throw std::runtime_error("Failed to create text surface: " +
                               std::string(TTF_GetError()));
    }

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(globals.renderer.get(), surface);
    SDL_FreeSurface(surface);
    if (!texture) {
      throw std::runtime_error("Failed to create text texture: " +
                               std::string(SDL_GetError()));
    }

    it = textureCache.emplace(cacheKey, texture).first;
  }

  int textWidth, textHeight;
  SDL_QueryTexture(it->second, NULL, NULL, &textWidth, &textHeight);
  if (textWidth <= 0 || textHeight <= 0 || bounds.w <= 0 || bounds.h <= 0)
    return;

  SDL_FRect destRect = {bounds.x, bounds.y, static_cast<float>(textWidth),
                        static_cast<float>(textHeight)};
  if (destRect.w > bounds.w || destRect.h > bounds.h) {
    const float scaleX = static_cast<float>(bounds.w) / textWidth;
    const float scaleY = static_cast<float>(bounds.h) / textHeight;
    const float scale = scaleX < scaleY ? scaleX : scaleY;
    destRect.w = static_cast<int>(textWidth * scale);
    destRect.h = static_cast<int>(textHeight * scale);
  }

  if (centered) {
    destRect.x = bounds.x + (bounds.w - destRect.w) / 2;
    destRect.y = bounds.y + (bounds.h - destRect.h) / 2;
  }

  SDL_RenderCopyF(globals.renderer.get(), it->second, NULL, &destRect);
}

int Text::getWidth(const std::string &text) {
  int width = 0;
  int height = 0;
  if (TTF_SizeText(font, text.c_str(), &width, &height) != 0) {
    throw std::runtime_error("Failed to measure text: " +
                             std::string(TTF_GetError()));
  }
  return width;
}

int Text::getHeight(const std::string &text) {
  int width = 0;
  int height = 0;
  if (TTF_SizeText(font, text.c_str(), &width, &height) != 0) {
    throw std::runtime_error("Failed to measure text: " +
                             std::string(TTF_GetError()));
  }
  return height;
}

void Text::clear() {
  // Free cached textures
  for (auto &[text, texture] : textureCache) {
    SDL_DestroyTexture(texture);
  }
  if (font)
    TTF_CloseFont(font);
}

} // namespace tebya