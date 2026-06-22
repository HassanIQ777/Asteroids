#include "../TebyaEngine/src/Scene.cpp"
#include "Tebya/Button.hpp"
#include "Tebya/Colors.hpp"
#include "Tebya/Globals.hpp"
#include <SDL2/SDL_rect.h>

namespace Asteroids {
using tebya::Scene;

enum class UI_State { StartMenu, Playing, DeathMenu };

inline void initStartMenu(tebya::Globals &g, Scene &start_menu,
                          tebya::Text &label_text,
                          Asteroids::UI_State &ui_state) {

  static constexpr float btn_height = 75;
  static const float start_height = static_cast<float>(g.height) / 2;

  // Play button
  start_menu.add<tebya::Button>("play",
                                SDL_FRect{5, start_height, 150, btn_height},
                                [&]() { ui_state = UI_State::Playing; });

  start_menu.get("play")->setLabel(&label_text, "Play");
  start_menu.get("play")->setColors(
      tebya::Colors::WithAlpha(tebya::Colors::GhostWhite, 200),
      tebya::Colors::WithAlpha(tebya::Colors::ShadowBlack, 100));

  // quit button
  start_menu.add<tebya::Button>(
      "quit", SDL_FRect{5, start_height + btn_height, 150, btn_height},
      [&]() { g.running = false; });

  start_menu.get("quit")->setLabel(&label_text, "Quit");
  start_menu.get("quit")->setColors(
      tebya::Colors::WithAlpha(tebya::Colors::GhostWhite, 200),
      tebya::Colors::WithAlpha(tebya::Colors::ShadowBlack, 100));
}

inline void initDeathMenu(tebya::Globals &g, Scene &death_menu,
                          tebya::Text &label_text,
                          Asteroids::UI_State &ui_state) {}

} // namespace Asteroids