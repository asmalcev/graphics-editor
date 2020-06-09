#pragma once
#include "Interfaces/Tool.hpp"
#include "../main/graphicsEditor.hpp"

class LineInstrument : public Tool {
private:
  Point * firstPoint;
  Point * secondPoint;
public:
  LineInstrument();
  ~LineInstrument();
  void draw(SDL_Surface*,int,int,SDL_Rect) override;
  void finishDraw(SDL_Surface *, SDL_Rect) override;
};