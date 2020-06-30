#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Model/DataModel.hpp"
#include "FillerInstrument.hpp"
#include "Stack/Stack.hpp"
#include "main/utils.hpp"

#include <iostream>

void FillerInstrument::draw(int x, int y, SDL_Rect bound) {
  pos.x = x;
  pos.y = y;
}

void FillerInstrument::finishDraw(SDL_Rect bound) {
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    SDL_Surface * surf = DataModel::getData()->getCanvasSurface();

    Uint32 newColor = DataModel::getData()->getChoosenColor();
    Uint32 oldColor = getpixel(surf, pos.x - bound.x, pos.y - bound.y);
    if (newColor == oldColor) return;
    Stack<Point> st;
    st.push(Point(pos.x - bound.x, pos.y - bound.y));

    int y1, spanLeft, spanRight;
    while (!st.isEmpty()) {
      Point p(st.pull());
      y1 = p.y;

      while (y1 >= 0 && getpixel(surf, p.x, y1) == oldColor) y1--;
      y1++;
      spanLeft = spanRight = 0;

      while (y1 < bound.h && getpixel(surf, p.x, y1) == oldColor) {
        Draw_Pixel(surf, p.x, y1, newColor);
        if (spanLeft == 0 && p.x > 0 && getpixel(surf, p.x - 1, y1) == oldColor) {
          st.push(Point(p.x - 1, y1));
          spanLeft = 1;
        } else if (spanLeft == 1 && p.x > 0 && getpixel(surf, p.x - 1, y1) != oldColor) {
          spanLeft = 0;
        }

        if (spanRight == 0 && p.x < bound.w && getpixel(surf, p.x + 1, y1) == oldColor) {
          st.push(Point(p.x + 1, y1));
          spanRight = 1;
        } else if (spanRight == 1 && p.x < bound.w && getpixel(surf, p.x + 1, y1) != oldColor) {
          spanRight = 0;
        }

        y1++;
      }
    }
    updateCanvasScreen(&bound);
  }
  pos.x = 0;
  pos.y = 0;
}
