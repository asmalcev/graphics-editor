#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Controller/Controller.hpp"
#include "Modal.hpp"
#include "Model/DataModel.hpp"
#include "main/graphicsEditor.hpp"
#include <cstring>

Modal::Modal(
  int w,
  int h,
  const style_s * windowStyle
) : 
  Window(window_width / 2 - w / 2, window_height / 2 - h / 2, w, h, windowStyle),
  txtInput(nullptr),
  actionBtn(nullptr),
  cancelBtn(nullptr)
{
  tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
    SDL_DOUBLEBUF, window_width, window_height, window_scrdepth,
    screen->format->Rmask, screen->format->Gmask,
    screen->format->Bmask, screen->format->Amask);
}

Modal::~Modal() {
  SDL_FreeSurface(tmp);
  delete txtInput;
  delete actionBtn;
  delete cancelBtn;
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
  if (actionBtn != nullptr) actionBtn->draw();
  if (cancelBtn != nullptr) cancelBtn->draw();
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
    if (actionBtn != nullptr && actionBtn->clicked(event)) return true;
    if (cancelBtn != nullptr && cancelBtn->clicked(event)) return true;
    Controller::getController()->clearFocusedObj();
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
    if (actionBtn != nullptr && actionBtn->hovered(event)) return true;
    if (cancelBtn != nullptr && cancelBtn->hovered(event)) return true;
    Controller::getController()->clearHoveredObj();
    return true;
	}
  return false;
}

void Modal::setInput(int x, int y, int w, int h) {
  char * cstr = new char[DataModel::getData()->getFilePath().length() + 1];
	strcpy(cstr, DataModel::getData()->getFilePath().c_str());
  txtInput = new TextInput(pos.x + x, pos.y + y, w, h, &textInputStyle, (char *) "File path", cstr, ComponentName::FilePath, false);
	delete [] cstr;
}

void Modal::setActionBtn(int x, int y, int w, int h, char * actionText, ComponentName name) {
  if (actionBtn != nullptr) {
    delete actionBtn;
  }
  actionBtn = new Button(pos.x + x, pos.y + y, w, h, &btnStyle, (char *) "Confirm", actionText, name, false, false);
}

void Modal::setCancelBtn(int x, int y, int w, int h) {
  if (cancelBtn != nullptr) {
    delete cancelBtn;
  }
  cancelBtn = new Button(pos.x + x, pos.y + y, w, h, &btnStyle, (char *) "Cancel", (char *) "Close modal window", ComponentName::Cancel, false, false);
}