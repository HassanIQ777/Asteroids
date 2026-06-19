#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

#include "Globals.hpp"

namespace tebya {

class Text {
private:
  Globals &globals;
  TTF_Font *font;
  std::unordered_map<std::string, SDL_Texture *> textureCache;

public:
  Text(Globals &globals_, const std::string &fontPath, int fontSize);

  ~Text();

  void render(const std::string &text, int x, int y, SDL_Color color,
              bool centered = false);

  void renderInside(const std::string &text, SDL_FRect bounds, SDL_Color color,
                    bool centered = false);

  int getWidth(const std::string &text);

  int getHeight(const std::string &text);

  void clear();
}; // end class Text

} // namespace tebya
