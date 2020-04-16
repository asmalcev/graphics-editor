#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "graphicsEditor.hpp"
#include "ColorInput.hpp"
#include "Controller.hpp"
#include "utils.hpp"

ColorInput::ColorInput(
  SDL_Surface* screenSurface,
  int x,
  int y,
  int w,
  int h,
  const Style* inputStyle,
  Uint32 color,
  char* tooltip
) {
  screen = screenSurface;
  style = inputStyle;
  tooltipText = tooltip;

  pos.x = x + style->margin;
  pos.y = y + style->margin;
  pos.w = w - style->margin;
  pos.h = h - style->margin;

  TTF_SizeText(TTF_OpenFont("../public/Ubuntu.ttf", style->tooltipTextFontSize), tooltipText ,&textWidth, &textHeight);
  textHeight += 2;
  textWidth += 6;

  isHovered = isFocused = false;
  colorValue = color;
  
  tmpForTooltip = SDL_CreateRGBSurface(SDL_HWSURFACE |
    SDL_DOUBLEBUF, textWidth, textHeight, window_scrdepth,
    screen->format->Rmask, screen->format->Gmask,
    screen->format->Bmask, screen->format->Amask);
  this->draw();
}

bool ColorInput::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    toggleFocusedDraw();
    Controller::getController()->changeFocus(this);
    return true;
	}
  return false;
}

void ColorInput::toggleFocusedDraw() {
  isFocused = !isFocused;
}