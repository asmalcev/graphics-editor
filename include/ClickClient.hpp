#pragma once
#include <SDL/SDL.h>

class ClickClient {
public:
  virtual bool clicked(SDL_Event*) = 0;
};