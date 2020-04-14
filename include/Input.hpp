#pragma once
#include "graphicsEditor.hpp"
#include <SDL/SDL.h>

class Input {
protected:
  SDL_Rect pos;
  SDL_Surface* screen, *tmpForTooltip;
  const Style* style;
	char* tooltipText;
  bool isFocused, isHovered;
	int textWidth, textHeight;

public:
  virtual void draw() = 0;
  virtual SDL_Rect getBound() = 0;
  virtual void drawClicked() = 0;
  virtual void drawTooltip() = 0;

};