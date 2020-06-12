#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "ClearInstrument.hpp"
#include "main/graphicsEditor.hpp"

void ClearInstrument::finishDraw(SDL_Surface * screen, SDL_Rect bound) {
  Draw_FillRect(screen, bound.x, bound.y, bound.w, bound.h, mainColor);
  SDL_Flip(screen);
}