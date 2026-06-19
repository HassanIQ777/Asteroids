#pragma once

#include "Text.hpp"
#include "Texture.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <string>

namespace tebya {

enum class WidgetState { Hovered, Clicked, Nothing };

class Widget {
protected:
  WidgetState state = WidgetState::Nothing;
  bool isVisible = true;
  SDL_FRect bounds{};
  std::string label;
  Text *label_text = nullptr;
  Texture *texture = nullptr;
  SDL_Color text_color = {255, 255, 255, 255}, background_color{0, 0, 0, 255};

public:
  virtual ~Widget() = default;
  virtual void render() = 0;
  virtual void update() = 0;

  void updateState();
  WidgetState getState() const { return state; }

  void setVisibility(bool visibility) { isVisible = visibility; }
  bool getVisibility() const { return isVisible; }

  void setBounds(SDL_FRect r) { bounds = r; }
  SDL_FRect getBounds() const { return bounds; }

  void setLabel(Text *label_text, const std::string &label) {
    this->label_text = label_text;
    this->label = label;
  }
  std::string getLabel() const { return label; }

  void setTexture(Texture *texture) { this->texture = texture; }
  Texture *getTexture() const { return texture; }

  void setColors(SDL_Color text_color, SDL_Color background_color) {
    this->text_color = text_color;
    this->background_color = background_color;
  }
};

} // namespace tebya