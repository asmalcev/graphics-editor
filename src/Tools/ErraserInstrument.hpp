#pragma once
#include "Interfaces/Tool.hpp"

class ErraserInstrument : public Tool {
public:
  void draw(int,int,SDL_Rect) override;
  void finishDraw(SDL_Rect) override {};
};