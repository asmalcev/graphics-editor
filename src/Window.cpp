#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "graphicsEditor.hpp"
#include "Button.hpp"
#include "Window.hpp"

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

void Window::addButton(int x, int y, int w, int h, const Style* btnStyle, char* imgPath) {
  btns.push_back(Button(screen, pos.x + x, pos.y + y, w, h, btnStyle, imgPath));
  clickerListeners.push_back(&btns[btns.size() - 1]);
}

bool Window::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
		for (size_t i = 0; i < clickerListeners.size(); i++) {
      if (clickerListeners[i]->clicked(event)) break;
    }
    return true;
	}
  return false;
}