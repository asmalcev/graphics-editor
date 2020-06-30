#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "LineInstrument.hpp"
#include "Model/DataModel.hpp"
#include "main/graphicsEditor.hpp"
#include "main/utils.hpp"

void LineInstrument::draw(int x, int y, SDL_Rect bound) {
  updateCanvasScreen(&bound);
  if (firstPoint.x == -1) {
    firstPoint.x = x;
    firstPoint.y = y;
  } else {
    secondPoint.x = x;
    secondPoint.y = y;

    int width = DataModel::getData()->getLineWidth();
    int xcoord, ycoord, xcoord2, ycoord2;

    if (width == 1) {
      Draw_Line(
        screen, 
        firstPoint.x, 
        firstPoint.y, 
        secondPoint.x,
        secondPoint.y,
        DataModel::getData()->getChoosenColor());
    } else {
      for (int i = -width / 2; i < width / 2; i++) {
        for (int j = -width / 2; j < width / 2; j++) {
          xcoord = firstPoint.x + i;
          ycoord = firstPoint.y + j;
          xcoord2 = secondPoint.x + i;
          ycoord2 = secondPoint.y + j;
          if (
            (xcoord >= bound.x && xcoord < bound.w + bound.x  &&
             ycoord >= bound.y && ycoord < bound.h + bound.y) &&
            (xcoord2 >= bound.x && xcoord2 < bound.w + bound.x &&
             ycoord2 >= bound.y && ycoord2 < bound.h + bound.y)
          )
          Draw_Line(
            screen, 
            xcoord, 
            ycoord, 
            xcoord2,
            ycoord2,
            DataModel::getData()->getChoosenColor());
        }
      }
    }
    SDL_Flip(screen);
  }
}

void LineInstrument::finishDraw(SDL_Rect bound) {
  if (
    secondPoint.x >= bound.x && secondPoint.x < bound.w + bound.x &&
    secondPoint.y >= bound.y && secondPoint.y < bound.h + bound.y
  ) {
    firstPoint.x = -1;
    secondPoint.x = -1;
    
    updateCanvasSurface(&bound);
  }
}
