#include "Tebya/Texture.hpp"
#include <SDL2/SDL_render.h>
#include <cmath>

namespace tebya {

Texture::Texture(Globals &globals, const std::string &texture_path, size_t id_)
    : id(id_) {
  texture = IMG_LoadTexture(globals.renderer.get(), texture_path.c_str());
}

Texture::~Texture() { SDL_DestroyTexture(texture); }

SDL_Texture *Texture::getTexture() { return texture; }

size_t Texture::getId() const { return id; }

void Texture::render(Globals &globals, const SDL_FRect &dest) const {
  SDL_RenderCopyF(globals.renderer.r, texture, NULL, &dest);
}

void Texture::render(Globals &globals, const SDL_FRect &dest,
                     float angle) const {
  SDL_RenderCopyExF(globals.renderer.r, texture, NULL, &dest, angle, NULL,
                    flip);
}
void Texture::setFlip(SDL_RendererFlip flip) { this->flip = flip; }

} // namespace tebya