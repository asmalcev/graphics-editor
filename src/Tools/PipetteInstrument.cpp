#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Model/DataModel.hpp"
#include "PipetteInstrument.hpp"
#include "main/utils.hpp"

void PipetteInstrument::draw(int x, int y, SDL_Rect bound) {
  pos.x = x;
  pos.y = y;
}

void PipetteInstrument::finishDraw(SDL_Rect bound) {
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    DataModel::getData()->setChoosenColor(getpixel(screen, pos.x, pos.y));
    pos.x = 0;
    pos.y = 0;
  }
}
