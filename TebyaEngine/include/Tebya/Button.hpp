#pragma once

#include "Widget.hpp"
#include <SDL2/SDL_rect.h>
#include <functional>

namespace tebya {

class Button : public Widget {
  std::function<void()> onClick = nullptr;

public:
  Button(SDL_FRect bounds, std::function<void()> onClick) : onClick(onClick) {
    this->bounds = bounds;
  }

  void render() override;
  void update() override;
  bool isClicked();
};

} // namespace tebya