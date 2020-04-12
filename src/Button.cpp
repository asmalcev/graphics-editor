#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "graphicsEditor.hpp"
#include "Button.hpp"

#include <iostream>

Button::Button(
  SDL_Surface* screenSurface,
  int x,
  int y,
  int w,
  int h,
  const Style* btnStyle,
  char* imgPath
) {
  style = btnStyle;
  pos.x = x + style->margin;
  pos.y = y + style->margin;
  pos.w = w - style->margin;
  pos.h = h - style->margin;
  screen = screenSurface;
  img = imgPath;
  Button::draw();
}

void Button::draw() {
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
  Draw_FillRect(screen, pos.x, pos.y, pos.w, pos.h, style->color);
  SDL_BlitSurface(SDL_LoadBMP(img), NULL, screen, &pos);
}

SDL_Rect Button::getBound() {
  return pos;
}

bool Button::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    std::cout << img << std::endl;
    return true;
	}
  return false;
}

Button::~Button() {}