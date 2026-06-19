#include "Tebya/TextureManager.hpp"

namespace tebya {

// if caller own the object
void TextureManager::addTexture(std::unique_ptr<Texture> texture) {
  textures[texture->getId()] = std::move(texture);
}

//  Move from const reference:
void TextureManager::addTexture(
    Texture texture) { // Pass by value, move semantics kick in
  textures[texture.getId()] = std::make_unique<Texture>(std::move(texture));
}

Texture *TextureManager::getTexture(size_t id) {
  auto it = textures.find(id);
  return (it != textures.end()) ? it->second.get() : nullptr;
}

// Const variant
const Texture *TextureManager::getTexture(size_t id) const {
  auto it = textures.find(id);
  return (it != textures.end()) ? it->second.get() : nullptr;
}

// Remove a texture
bool TextureManager::removeTexture(size_t id) { return textures.erase(id) > 0; }

} // namespace tebya