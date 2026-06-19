#include "Tebya/Button.hpp"
#include "Tebya/Globals.hpp"
#include "Tebya/Widget.hpp"
#include <SDL2/SDL_render.h>

namespace tebya {

void Button::render() {
  if (!isVisible) {
    return;
  }
  Globals &globals = Globals::getInstance();
  if (texture != nullptr) {
    texture->render(globals, bounds);
  } else {
    SDL_SetRenderDrawColor(globals.renderer.r, background_color.r,
                           background_color.g, background_color.b,
                           background_color.a);
    SDL_RenderFillRectF(globals.renderer.r, &bounds);
  }
  if (!label.empty() && label_text != nullptr) {
    label_text->renderInside(label, bounds, text_color, true);
  }
}

void Button::update() {
  updateState();
  if (isClicked() && onClick != nullptr) {
    onClick();
  }
}

bool Button::isClicked() { return state == WidgetState::Clicked; }

} // namespace tebya