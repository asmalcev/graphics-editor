#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "window.hpp"

Window::Window(SDL_Surface* screenSurface, int x, int y, int w, int h, Uint32 color) {
  pos.x = x;
  pos.y = y;
  pos.w = w;
  pos.h = h;
  screen = screenSurface;
  Window::draw(color);
}

void Window::draw(Uint32 color) {
  const Sint16 shadowOffset = 4;
  Draw_FillRect(screen, (Sint16) (pos.x + shadowOffset), (Sint16) (pos.y + pos.h), pos.w, shadowOffset, SDL_MapRGB(screen->format, 55,71,79));
  Draw_FillRect(screen, (Sint16) (pos.x + pos.w), (Sint16) (pos.y + shadowOffset), shadowOffset, (Uint16) (pos.h - shadowOffset), SDL_MapRGB(screen->format, 55,71,79));
  Draw_FillRect(screen, pos.x, pos.y, pos.w, pos.h, color);
}

SDL_Rect Window::getBound() {
  return pos;
}