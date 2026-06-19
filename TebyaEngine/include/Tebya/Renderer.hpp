#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

namespace tebya {

class Renderer {
public:
  SDL_Renderer *r;
  Renderer(SDL_Renderer *renderer);

  SDL_Renderer *get() const;

  void drawCircle(int x, int y, int radius, float density = 0.1f);

  void drawRect(SDL_Rect, SDL_Color color);
  void drawRectF(SDL_FRect, SDL_Color color);
  void drawRectFilled(SDL_Rect rect, SDL_Color color);
  void drawRectFilledF(SDL_FRect rect, SDL_Color color);

  void drawThickLine(float x1, float y1, float x2, float y2, float thickness);

  void clear();
  void clear(SDL_Color color);
  void setColor(SDL_Color color);

  void present();
};

} // namespace tebya