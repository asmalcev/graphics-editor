#pragma once
#include "Interfaces/Tool.hpp"

class PencilInstrument : public Tool {
public:
  void draw(SDL_Surface*,int,int,SDL_Rect) override;
  void finishDraw(SDL_Surface *,SDL_Rect) override {};
};