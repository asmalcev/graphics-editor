#pragma once
#include "Interfaces/Tool.hpp"
#include "../main/graphicsEditor.hpp"

class LineInstrument : public Tool {
private:
  Point * firstPoint;
  Point * secondPoint;
  Point * lastSecondPoint;
  SDL_Surface * tmp;
public:
  LineInstrument();
  ~LineInstrument();
  void draw(SDL_Surface*,int,int,SDL_Rect) override;
  void finishDraw(SDL_Surface *) override;
};