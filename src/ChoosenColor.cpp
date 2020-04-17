#include "Controller.hpp"
#include "ChoosenColor.hpp"

ChoosenColor::ChoosenColor(
  SDL_Surface* screenSurface,
  int x,
  int y,
  int w,
  int h,
  const style_s* inputStyle,
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

void ChoosenColor::draw() {
  Draw_FillRect(screen, 
    (Sint16) (pos.x + style->shadowOffset),
    (Sint16) (pos.y + pos.h),
    pos.w, style->shadowOffset,
    style->shadowColor);
  Draw_FillRect(screen,
    (Sint16) (pos.x + pos.w),
    (Sint16) (pos.y + style->shadowOffset),
    style->shadowOffset,
    (Uint16) (pos.h - style->shadowOffset),
    style->shadowColor);
  Draw_FillRect(screen, pos.x, pos.y, pos.w, pos.h, colorValue);
  Draw_Rect(screen, pos.x, pos.y, pos.w, pos.h, style->color);
}

bool ChoosenColor::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (Controller::getController()->changeHover(this)) toggleHoveredDraw();
    return true;
	}
  return false;
}

void ChoosenColor::toggleHoveredDraw() {
  if (isHovered) {
    SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), 100, 20};
    SDL_BlitSurface(tmpForTooltip, NULL, screen, &tooltipPos);
  } else {
   drawTooltip(); 
  }
  SDL_Flip(screen);
  isHovered = !isHovered;
}