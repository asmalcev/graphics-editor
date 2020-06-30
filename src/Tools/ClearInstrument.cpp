#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "ClearInstrument.hpp"
#include "main/graphicsEditor.hpp"
#include "main/utils.hpp"
#include "Model/DataModel.hpp"

void ClearInstrument::draw(int x, int y, SDL_Rect bound) {
  pos.x = x;
  pos.y = y;
}

void ClearInstrument::finishDraw(SDL_Rect bound) {
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    SDL_Surface * surf = DataModel::getData()->getCanvasSurface();

    Draw_FillRect(surf, 0, 0, bound.w, bound.h, mainColor);
    pos.x = 0;
    pos.y = 0;
    updateCanvasScreen(&bound);
  }
}