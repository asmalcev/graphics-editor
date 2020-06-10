#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Controller/Controller.hpp"
#include "Modal.hpp"

Modal::Modal(
  SDL_Surface * screenSurface,
  int w,
  int h,
  const style_s * windowStyle
) : opened(false) {
  style = windowStyle;
  screen = screenSurface;

  int xcenter = window_width / 2;
  int ycenter = window_height / 2;
  pos.x = xcenter - w / 2;
  pos.y = ycenter - h / 2;
  pos.w = w;
  pos.h = h;

  tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
    SDL_DOUBLEBUF, window_width, window_height, window_scrdepth,
    screen->format->Rmask, screen->format->Gmask,
    screen->format->Bmask, screen->format->Amask);
}

Modal::~Modal() {
  SDL_FreeSurface(tmp);
}

SDL_Rect Modal::getBound() {
  return pos;
}

void Modal::draw() {
  if (opened) {
    SDL_BlitSurface(tmp, NULL, screen, NULL);
  } else {
    SDL_BlitSurface(screen, NULL, tmp, NULL);
    Draw_FillRect(screen, 0, 0, window_width, window_height, backgroundColor);
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
    addText(84, 12, (char*) "Input relative or absolute path", 18, 0x333333);
    addText(84, 30, (char*) "with name and ends with .bmp", 18, 0x333333);
  }
  SDL_Flip(screen);
  opened = !opened;
}

bool Modal::clicked(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    return true;
	}
  return false;
}

bool Modal::hovered(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    return true;
	}
  return false;
}