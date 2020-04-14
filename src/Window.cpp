#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "graphicsEditor.hpp"
#include "Window.hpp"
#include "utils.hpp"

#include <iostream>

Window::Window(SDL_Surface* screenSurface, int x, int y, int w, int h, const Style* windowStyle) {
  style = windowStyle;
  screen = screenSurface;

  pos.x = x + style->margin;
  pos.y = y + style->margin;
  pos.w = w - style->margin;
  pos.h = h - style->margin;
  
  Window::draw();
}

void Window::draw() {
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
}

SDL_Rect Window::getBound() {
  return pos;
}

void Window::addButton(
  int x,
  int y,
  int w,
  int h,
  const Style* btnStyle,
  char* imgPath,
  char* tooltip
) {
  btns.push_back(Button(screen, pos.x + x, pos.y + y, w, h, btnStyle, imgPath, tooltip));
}

void Window::addTextInput(
  int x,
  int y,
  int w,
  int h,
  const Style* textInputStyle,
  char* tooltip
) {
  textInputs.push_back(TextInput(screen, pos.x + x, pos.y + y, w, h, textInputStyle, tooltip));
}

bool Window::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
		for (size_t i = 0; i < btns.size(); i++)
      if (btns[i].clicked(event)) break;

    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i].clicked(event)) break;

    return true;
	}
  return false;
}

bool Window::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
		for (size_t i = 0; i < btns.size(); i++)
      if (btns[i].hovered(event)) return true;
    
    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i].hovered(event)) return true;
	}
  return false;
}

void Window::addText(int x, int y, char* text, int fontSize, Uint32 color) {
  SDL_Rect textPos = {(Sint16) (pos.x + x),(Sint16) (pos.y + y), 0, 0};
  renderText(screen, textPos, text, fontSize, color);
}