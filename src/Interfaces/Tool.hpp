#pragma once
#include <SDL/SDL.h>

class Tool {
public:
  virtual void draw(SDL_Surface *,int,int,SDL_Rect) = 0;
  virtual void finishDraw(SDL_Surface *) = 0;
};