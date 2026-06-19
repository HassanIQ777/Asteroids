#include "Tebya/Widget.hpp"
#include "Tebya/Collision.hpp"
#include "Tebya/Globals.hpp"

namespace tebya {

void Widget::updateState() {
  Globals &globals = Globals::getInstance();
  const int x = globals.input.getMouseX();
  const int y = globals.input.getMouseY();
  const SDL_FRect mouse = {static_cast<float>(x), static_cast<float>(y), 1, 1};

  WidgetState state = WidgetState::Nothing; // first we assume it's nothing
  if (Collision::AABB(mouse, bounds) != CollisionSide::None) {
    state = WidgetState::Hovered;
  }
  if (state == WidgetState::Hovered &&
      globals.input.isMouseButtonPressed(MouseButton::LEFT)) {
    state = WidgetState::Clicked;
  }
  this->state = state;
}

} // namespace tebya