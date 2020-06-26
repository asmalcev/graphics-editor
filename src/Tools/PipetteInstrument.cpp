#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Model/DataModel.hpp"
#include "PipetteInstrument.hpp"
#include "main/utils.hpp"

void PipetteInstrument::draw(int x, int y, SDL_Rect bound) {
  pos.x = x;
  pos.y = y;
}

void PipetteInstrument::finishDraw(SDL_Rect bound) {
  DataModel::getData()->setChoosenColor(getpixel(screen, pos.x, pos.y));
}
