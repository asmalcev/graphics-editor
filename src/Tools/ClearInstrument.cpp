#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "ClearInstrument.hpp"
#include "main/graphicsEditor.hpp"

void ClearInstrument::draw(int x, int y, SDL_Rect bound) {
  pos.x = x;
  pos.y = y;
}

void ClearInstrument::finishDraw(SDL_Rect bound) {
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    Draw_FillRect(screen, bound.x, bound.y, bound.w, bound.h, mainColor);
    SDL_Flip(screen);
    pos.x = 0;
    pos.y = 0;
  }
}