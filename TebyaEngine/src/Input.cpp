#include "Tebya/Input.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

namespace tebya {

InputManager::InputManager() {
  keystate = SDL_GetKeyboardState(&key_count);
  prev_mouse_state = mouse_state;
}

InputManager::~InputManager() = default;

void InputManager::update(const SDL_Event &event) {
  reset();
  if (event.type == SDL_MOUSEMOTION) {
    mouse_state.x = event.motion.x;
    mouse_state.y = event.motion.y;
  } else if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT)
      mouse_state.left = true;
    if (event.button.button == SDL_BUTTON_RIGHT)
      mouse_state.right = true;
    if (event.button.button == SDL_BUTTON_MIDDLE)
      mouse_state.middle = true;
  } else if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT)
      mouse_state.left = false;
    if (event.button.button == SDL_BUTTON_RIGHT)
      mouse_state.right = false;
    if (event.button.button == SDL_BUTTON_MIDDLE)
      mouse_state.middle = false;
  }
  // NEW: Handle scroll
  else if (event.type == SDL_MOUSEWHEEL) {
    scrollDelta = event.wheel.y;
    scrollDeltaX = event.wheel.x;
  }
}

void InputManager::reset() {
  prev_mouse_state = mouse_state; // snapshot BEFORE new events arrive
  scrollDelta = 0;
  scrollDeltaX = 0;
  pollKeyboard(); // also put this here if it isn't called elsewhere
}

void InputManager::pollKeyboard() {
  // Shift history bits and update current state
  for (int i = 0; i < key_count; ++i) {
    uint8_t &history = key_history[i];
    history = (history << 1) | (keystate[i] ? 1 : 0);
  }
}

bool InputManager::isMouseButtonPressed(MouseButton button) const {
  switch (button) {
  case MouseButton::LEFT:
    return mouse_state.left;

  case MouseButton::RIGHT:
    return mouse_state.right;

  case MouseButton::MIDDLE:
    return mouse_state.middle;
  }
  return false;
}

bool InputManager::isKeyPressed(KeyCode key) const {
  const int index = static_cast<int>(key);
  return index >= 0 && index < key_count && (keystate[index] != 0);
}

bool InputManager::isKeyJustPressed(KeyCode key) const {
  const int index = static_cast<int>(key);
  if (index < 0 || index >= key_count)
    return false;
  // history bits: [...][prev][current]
  // just pressed = was 0, now 1 → 0b01
  auto it = key_history.find(index);
  return it != key_history.end() && (it->second & 0b11) == 0b01;
}

bool InputManager::isKeyJustReleased(KeyCode key) const {
  const int index = static_cast<int>(key);
  if (index < 0 || index >= key_count)
    return false;
  // just released = was 1, now 0 → 0b10
  auto it = key_history.find(index);
  return it != key_history.end() && (it->second & 0b11) == 0b10;
}

void InputManager::onKeyPress(KeyCode key, std::function<void()> callback) {
  key_callbacks[static_cast<int>(key)].push_back(callback);
}

} // namespace tebya
