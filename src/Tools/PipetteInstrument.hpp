#pragma once
#include "Interfaces/Tool.hpp"
#include "main/graphicsEditor.hpp"

class PipetteInstrument : public Tool {
  Point pos;
public:
  void draw(SDL_Surface *,int,int,SDL_Rect) override;
  void finishDraw(SDL_Surface *, SDL_Rect) override;
};