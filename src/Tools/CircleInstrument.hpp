#pragma once
#include "Interfaces/Tool.hpp"
#include "../main/graphicsEditor.hpp"

class CircleInstrument : public Tool {
private:
  Point * firstPoint;
  Point * secondPoint;
public:
  CircleInstrument();
  ~CircleInstrument();
  void draw(SDL_Surface*,int,int,SDL_Rect) override;
  void finishDraw(SDL_Surface *, SDL_Rect) override;
};