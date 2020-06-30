#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "ErraserInstrument.hpp"
#include "Model/DataModel.hpp"
#include "main/graphicsEditor.hpp"
#include "main/utils.hpp"

void ErraserInstrument::draw(int x, int y, SDL_Rect bound) {
  SDL_Surface * surf = DataModel::getData()->getCanvasSurface();

  x -= bound.x;
  y -= bound.y;
  
  int width = DataModel::getData()->getLineWidth();
  int xcoord, ycoord;
  if (width == 1) {
    Draw_Pixel(surf, x, y, mainColor);
  } else {
    for (int i = -width / 2; i < width / 2; i++) {
      for (int j = -width / 2; j < width / 2; j++) {
        xcoord = x + i;
        ycoord = y + j;
        if (
          xcoord >= 0 && xcoord < bound.w &&
          ycoord >= 0 && ycoord < bound.h
        )
        Draw_Pixel(surf, xcoord, ycoord, mainColor);
      }
    }
  }
  updateCanvasScreen(&bound);
}