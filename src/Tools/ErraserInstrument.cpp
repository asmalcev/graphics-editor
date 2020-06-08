#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "ErraserInstrument.hpp"
#include "Model/DataModel.hpp"
#include "../main/graphicsEditor.hpp"

void ErraserInstrument::draw(SDL_Surface* screen, int x, int y, SDL_Rect bound) {
  int width = DataModel::getData()->getLineWidth();
  int xcoord, ycoord;
  for (int i = -width / 2; i < width / 2; i++) {
    for (int j = -width / 2; j < width / 2; j++) {
      xcoord = x + i;
      ycoord = y + j;
      if (
        xcoord >= bound.x && xcoord < bound.w + bound.x &&
        ycoord >= bound.y && ycoord < bound.h + bound.y
      )
      Draw_Pixel(screen, xcoord, ycoord, mainColor);
    }
  }
  SDL_Flip(screen);
}