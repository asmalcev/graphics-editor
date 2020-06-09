#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "CircleInstrument.hpp"
#include "Model/DataModel.hpp"
#include "../main/graphicsEditor.hpp"
#include <cmath>

CircleInstrument::CircleInstrument() :
  firstPoint(nullptr), secondPoint(nullptr) {}

CircleInstrument::~CircleInstrument() {
  delete firstPoint;
  delete secondPoint;
}

void CircleInstrument::draw(SDL_Surface* screen, int x, int y, SDL_Rect bound) {
  if (firstPoint == nullptr) {
    firstPoint = new Point(x, y);
  } else {
    delete secondPoint;
    secondPoint = new Point(x, y);
  }
}

void CircleInstrument::finishDraw(SDL_Surface * screen, SDL_Rect bound) {
  if (secondPoint != nullptr) {
    int width = DataModel::getData()->getLineWidth();
    int xcoord, ycoord, xcoord2, ycoord2;

    if (width == 1) {
      Draw_Line(
        screen, 
        firstPoint->x, 
        firstPoint->y, 
        secondPoint->x,
        secondPoint->y,
        DataModel::getData()->getChoosenColor());
    } else {
      for (int i = -width / 2; i < width / 2; i++) {
        for (int j = -width / 2; j < width / 2; j++) {
          xcoord = firstPoint->x + i;
          ycoord = firstPoint->y + j;
          xcoord2 = secondPoint->x + i;
          ycoord2 = secondPoint->y + j;
          if (
            (xcoord >= bound.x && xcoord < bound.w + bound.x &&
            ycoord >= bound.y && ycoord < bound.h + bound.y) &&
            (xcoord2 >= bound.x && xcoord2 < bound.w + bound.x &&
            ycoord2 >= bound.y && ycoord2 < bound.h + bound.y)
          )
          Draw_Ellipse(
            screen, 
            abs(xcoord + xcoord2) / 2,
            abs(ycoord + ycoord2) / 2,
            abs(xcoord - xcoord2) / 2,
            abs(ycoord - ycoord2) / 2,
            DataModel::getData()->getChoosenColor());
        }
      }
    }
  }
  
  delete firstPoint;
  delete secondPoint;
  firstPoint = nullptr;
  secondPoint = nullptr;
  SDL_Flip(screen);
}
