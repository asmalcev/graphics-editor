#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Controller/Controller.hpp"
#include "Modal.hpp"
#include "main/graphicsEditor.hpp"
#include <iostream>

Modal::Modal(
  int w,
  int h,
  const style_s * windowStyle
) : Window(window_width / 2 - w / 2, window_height / 2 - h / 2, w, h, windowStyle), txtInput(nullptr), m_confirm(nullptr)  {
  tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
    SDL_DOUBLEBUF, window_width, window_height, window_scrdepth,
    screen->format->Rmask, screen->format->Gmask,
    screen->format->Bmask, screen->format->Amask);
}

Modal::~Modal() {
  SDL_FreeSurface(tmp);
  delete txtInput;
  delete m_confirm;
}

void Modal::draw(SDL_Surface * surf) {
  SDL_BlitSurface(surf, NULL, tmp, NULL);
  Draw_FillRect(surf, 0, 0, window_width, window_height, backgroundColor);
  Draw_FillRect(surf, 
    (Sint16) (pos.x + style->shadowOffset), 
    (Sint16) (pos.y + pos.h),
    pos.w, style->shadowOffset, 
    style->shadowColor);
  Draw_FillRect(surf,
    (Sint16) (pos.x + pos.w),
    (Sint16) (pos.y + style->shadowOffset),
    style->shadowOffset,
    (Uint16) (pos.h - style->shadowOffset),
    style->shadowColor);
  Draw_FillRect(surf, pos.x, pos.y, pos.w, pos.h, style->color);
  if (txtInput != nullptr) txtInput->draw();
  if (m_confirm != nullptr) m_confirm->draw();
}

void Modal::close() {
  SDL_BlitSurface(tmp, NULL, screen, NULL);
}

bool Modal::clicked(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (txtInput != nullptr && txtInput->clicked(event)) return true;
    if (m_confirm != nullptr && m_confirm->clicked(event)) return true;
    return true;
	}
  return false;
}

bool Modal::hovered(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (txtInput != nullptr && txtInput->hovered(event)) return true;
    if (m_confirm != nullptr && m_confirm->hovered(event)) return true;
    Controller::getController()->clearHoveredObj();
    return true;
	}
  return false;
}

void Modal::setInput(int x, int y, int w, int h, char * tooltipTxt, char * holderTxt, ComponentName name) {
  txtInput = new TextInput(pos.x + x, pos.y + y, w, h, &textInputStyle, tooltipTxt, holderTxt, name, false);
}

void Modal::setConfirm(int x, int y, int w, int h) {
  m_confirm = new Confirm(pos.x + x, pos.y + y, w, h, &btnStyle);
}