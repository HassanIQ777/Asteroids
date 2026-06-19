#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <cstdint>
#include <functional>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

namespace tebya {

enum class KeyCode : int {

  // directions
  UP = SDL_SCANCODE_UP,
  DOWN = SDL_SCANCODE_DOWN,
  LEFT = SDL_SCANCODE_LEFT,
  RIGHT = SDL_SCANCODE_RIGHT,

  // letters
  A = SDL_SCANCODE_A,
  B = SDL_SCANCODE_B,
  C = SDL_SCANCODE_C,
  D = SDL_SCANCODE_D,
  E = SDL_SCANCODE_E,
  F = SDL_SCANCODE_F,
  G = SDL_SCANCODE_G,
  H = SDL_SCANCODE_H,
  I = SDL_SCANCODE_I,
  J = SDL_SCANCODE_J,
  K = SDL_SCANCODE_K,
  L = SDL_SCANCODE_L,
  M = SDL_SCANCODE_M,
  N = SDL_SCANCODE_N,
  O = SDL_SCANCODE_O,
  P = SDL_SCANCODE_P,
  Q = SDL_SCANCODE_Q,
  R = SDL_SCANCODE_R,
  S = SDL_SCANCODE_S,
  T = SDL_SCANCODE_T,
  U = SDL_SCANCODE_U,
  V = SDL_SCANCODE_V,
  W = SDL_SCANCODE_W,
  X = SDL_SCANCODE_X,
  Y = SDL_SCANCODE_Y,
  Z = SDL_SCANCODE_Z,

  // special
  SPACE = SDL_SCANCODE_SPACE,
  ENTER = SDL_SCANCODE_RETURN,
  ESCAPE = SDL_SCANCODE_ESCAPE,
  SHIFT = SDL_SCANCODE_LSHIFT,
  CTRL = SDL_SCANCODE_LCTRL,

  // others
  EQUALS = SDL_SCANCODE_EQUALS,
  MINUS = SDL_SCANCODE_MINUS
};

enum class MouseButton {
  LEFT = SDL_BUTTON_LEFT,
  MIDDLE = SDL_BUTTON_MIDDLE,
  RIGHT = SDL_BUTTON_RIGHT
};

struct MouseState {
  int x = 0, y = 0;
  bool left = false, right = false, middle = false;
};

class InputManager {
  const uint8_t *keystate = nullptr;
  int key_count = 0;

  std::unordered_map<int, uint8_t> key_history;

  // mouse states
  MouseState mouse_state;
  MouseState prev_mouse_state;

  // Scroll state (per frame)
  int scrollDelta = 0;  // How much scrolled THIS frame
  int scrollDeltaX = 0; // Horizontal scroll (bonus)

  // callbacks
  std::unordered_map<int, std::vector<std::function<void()>>> key_callbacks;

public:
  InputManager();
  ~InputManager();

  void update(const SDL_Event &e);
  void pollKeyboard();

  bool isKeyPressed(KeyCode key) const;
  bool isKeyJustPressed(KeyCode key) const;
  bool isKeyJustReleased(KeyCode key) const;

  bool isMouseButtonPressed(MouseButton button) const;
  bool isMouseButtonJustPressed(MouseButton button) const;

  int getMouseX() const { return mouse_state.x; }
  int getMouseY() const { return mouse_state.y; }
  int getMouseDeltaX() const { return mouse_state.x - prev_mouse_state.x; }
  int getMouseDeltaY() const { return mouse_state.y - prev_mouse_state.y; }

  int getScrollDelta() const { return scrollDelta; }
  int getScrollDeltaX() const { return scrollDeltaX; }
  bool isScrollingUp() const { return scrollDelta > 0; }
  bool isScrollingDown() const { return scrollDelta < 0; }
  bool isScrolling() const { return scrollDelta != 0; }

  void onKeyPress(KeyCode key, std::function<void()> callback);

  void reset();
};

} // namespace tebya