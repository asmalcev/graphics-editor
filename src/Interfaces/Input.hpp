#pragma once
#include <SDL/SDL.h>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "main/utils.hpp"

class Input {
protected:
  SDL_Rect pos;
  SDL_Surface * screen, * tmpForTooltip;
  const style_s * style;
	char * tooltipText;
  bool isFocused, isHovered;
	int textWidth, textHeight;
  ComponentName name;

public:
  virtual void draw() = 0;
  
  SDL_Rect getBound() {
    return pos;
  }

  void drawTooltip() {
    SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), (Uint16) textWidth, (Uint16) textHeight};
    SDL_BlitSurface(screen, &tooltipPos, tmpForTooltip, NULL);
    Draw_FillRect(screen,
      tooltipPos.x,
      tooltipPos.y,
      tooltipPos.w,
      tooltipPos.h, style->tooltipColor);
    Draw_Rect(screen,
      tooltipPos.x,
      tooltipPos.y,
      tooltipPos.w,
      tooltipPos.h, 0x333333);
    tooltipPos.x = (Sint16) (tooltipPos.x + 2);
    renderText(screen, tooltipPos, tooltipText, style->tooltipTextFontSize, style->tooltipTextColor);
  }

  ComponentName getComponentName() {
    return name;
  }

};