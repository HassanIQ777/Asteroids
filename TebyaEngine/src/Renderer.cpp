#include "Tebya/Renderer.hpp"
#include <SDL2/SDL_render.h>
#include <cmath>
#include <vector>

namespace tebya {

Renderer::Renderer(SDL_Renderer *renderer) : r(renderer) {}

SDL_Renderer *Renderer::get() const { return r; }

void Renderer::drawCircle(int x, int y, int radius, float density) {
  if (radius < 1)
    return;

  std::vector<SDL_FPoint> points;
  points.reserve(static_cast<size_t>(radius * 63) * density);
  for (float i = 0; i < 2 * M_PI; i += density) {
    float px = x + cos(i) * radius;
    float py = y + sin(i) * radius;
    points.push_back({px, py});
  }
  SDL_RenderDrawPointsF(r, points.data(), points.size());
}

void Renderer::drawRect(SDL_Rect rect, SDL_Color color) {
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(r, &rect);
}

void Renderer::drawRectF(SDL_FRect rect, SDL_Color color) {
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRectF(r, &rect);
}

void Renderer::drawRectFilled(SDL_Rect rect, SDL_Color color) {
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(r, &rect);
}

void Renderer::drawRectFilledF(SDL_FRect rect, SDL_Color color) {
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
  SDL_RenderFillRectF(r, &rect);
}

void Renderer::drawThickLine(float x1, float y1, float x2, float y2,
                             float thickness) {
  float dx = x2 - x1;
  float dy = y2 - y1;
  float len = std::sqrt(dx * dx + dy * dy);

  if (len > 0.0001f) {
    float px = -dy / len * thickness;
    float py = dx / len * thickness;

    SDL_RenderDrawLineF(r, x1 + px, y1 + py, x2 + px, y2 + py);
    SDL_RenderDrawLineF(r, x1 - px, y1 - py, x2 - px, y2 - py);
    SDL_RenderDrawLineF(r, x1, y1, x2, y2); // Center line for smoothness
  }
}

void Renderer::clear() { SDL_RenderClear(r); }
void Renderer::clear(SDL_Color color) {
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
  SDL_RenderClear(r);
}
void Renderer::setColor(SDL_Color color) {
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
}

void Renderer::present() { SDL_RenderPresent(r); }

} // namespace tebya