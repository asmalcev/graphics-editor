#pragma once
#include "Interfaces/Tool.hpp"
#include "main/graphicsEditor.hpp"

class LineInstrument : public Tool {
private:
  Point firstPoint;
  Point secondPoint;
public:
  void draw(int,int,SDL_Rect) override;
  void finishDraw(SDL_Rect) override;
};