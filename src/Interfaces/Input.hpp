#pragma once
#include <SDL/SDL.h>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "main/utils.hpp"

class Input {
protected:
  SDL_Rect pos;
  SDL_Surface * tmpForTooltip;
  const style_s * style;
	char * tooltipText;
  bool isFocused, isHovered;
	int textWidth, textHeight;
  ComponentName name;

public:
  Input(
    int x,
    int y,
    int w,
    int h,
    const style_s * inputStyle,
    char * tooltip,
    ComponentName className
  ) : style(inputStyle), tooltipText(tooltip), name(className) {
    pos.x = x + style->margin;
    pos.y = y + style->margin;
    pos.w = w - style->margin;
    pos.h = h - style->margin;

    TTF_SizeText(TTF_OpenFont("../public/Ubuntu.ttf", style->tooltipTextFontSize), tooltipText ,&textWidth, &textHeight);
    textHeight += 2;
    textWidth += 6;

    tmpForTooltip = SDL_CreateRGBSurface(SDL_HWSURFACE |
      SDL_DOUBLEBUF, textWidth, textHeight, window_scrdepth,
      screen->format->Rmask, screen->format->Gmask,
      screen->format->Bmask, screen->format->Amask);
  }
  virtual ~Input() {};
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