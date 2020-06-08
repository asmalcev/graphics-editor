#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "LineInstrument.hpp"
#include "Model/DataModel.hpp"
#include "../main/graphicsEditor.hpp"

#include <iostream>

LineInstrument::LineInstrument() :
  firstPoint(nullptr), secondPoint(nullptr), tmp(nullptr), lastSecondPoint(nullptr) {}

LineInstrument::~LineInstrument() {
  delete firstPoint;
  delete secondPoint;
  delete lastSecondPoint;
  SDL_FreeSurface(tmp);
}

void LineInstrument::draw(SDL_Surface* screen, int x, int y, SDL_Rect bound) {
  if (tmp == nullptr) {
    tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
      SDL_DOUBLEBUF, window_width, window_height, window_scrdepth,
      screen->format->Rmask, screen->format->Gmask,
      screen->format->Bmask, screen->format->Amask);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, SDL_MapRGB(tmp->format, 100,181,246));
	  Draw_FillRect(tmp, 0, 0, window_width, window_height, SDL_MapRGB(tmp->format, 100,181,246));
  }

  int width = DataModel::getData()->getLineWidth();
  int xcoord, ycoord;

  if (firstPoint == nullptr) {
    firstPoint = new Point(x, y);
  } else {
    SDL_Rect pos;
    if (lastSecondPoint != nullptr) {
      if (firstPoint->x < lastSecondPoint->x) {
        pos.x = firstPoint->x;
        pos.w = lastSecondPoint->x - firstPoint->x;
      } else {
        pos.x = lastSecondPoint->x;
        pos.w = firstPoint->x - lastSecondPoint->x;
      }

      if (firstPoint->y < lastSecondPoint->y) {
        pos.y = firstPoint->y;
        pos.h = lastSecondPoint->y - firstPoint->y;
      } else {
        pos.y = lastSecondPoint->y;
        pos.h = firstPoint->y - lastSecondPoint->y;
      }
      SDL_BlitSurface(tmp, NULL, screen, &pos);
    }

    delete secondPoint;
    secondPoint = new Point(x, y);
    if (firstPoint->x < secondPoint->x) {
      pos.x = firstPoint->x;
      pos.w = secondPoint->x - firstPoint->x;
    } else {
      pos.x = secondPoint->x;
      pos.w = firstPoint->x - secondPoint->x;
    }

    if (firstPoint->y < secondPoint->y) {
      pos.y = firstPoint->y;
      pos.h = secondPoint->y - firstPoint->y;
    } else {
      pos.y = secondPoint->y;
      pos.h = firstPoint->y - secondPoint->y;
    }

    SDL_BlitSurface(screen, &pos, tmp, NULL);
    Draw_Line(screen, firstPoint->x, firstPoint->y, secondPoint->x, secondPoint->y, DataModel::getData()->getLineWidth());
    delete lastSecondPoint;
    lastSecondPoint = new Point(*secondPoint);
  }
  
  // for (int i = -width / 2; i < width / 2; i++) {
  //   for (int j = -width / 2; j < width / 2; j++) {
  //     xcoord = x + i;
  //     ycoord = y + j;
  //     if (
  //       xcoord >= bound.x && xcoord < bound.w + bound.x &&
  //       ycoord >= bound.y && ycoord < bound.h + bound.y
  //     )
  //     Draw_Line(screen, firstPoint->x, firstPoint->y, secondPoint->x, secondPoint->y, DataModel::getData()->getLineWidth());
  //   }
  // }
}

void LineInstrument::finishDraw(SDL_Surface * screen) {
  delete firstPoint;
  delete secondPoint;
  delete lastSecondPoint;
  firstPoint = nullptr;
  secondPoint = nullptr;
  lastSecondPoint = nullptr;
  SDL_Flip(screen);
}
