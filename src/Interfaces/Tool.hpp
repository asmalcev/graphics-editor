#pragma once
#include <SDL/SDL.h>

class Tool {
public:
  virtual void draw(int,int,SDL_Rect) = 0;
  virtual void finishDraw(SDL_Rect) = 0;
};