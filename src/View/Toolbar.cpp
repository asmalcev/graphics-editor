#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "main/graphicsEditor.hpp"
#include "Toolbar.hpp"

Toolbar::Toolbar(
  int x,
  int y,
  int w,
  int h,
  const style_s* windowStyle
) : Window(x, y, w, h, windowStyle) {}

Toolbar::~Toolbar() {
  for (auto it = btns.begin(); it != btns.end(); it++) delete *it;
  for (auto it = textInputs.begin(); it != textInputs.end(); it++) delete *it;
}

void Toolbar::addButton(
  int x,
  int y,
  int w,
  int h,
  const style_s* btnStyle,
  char* imgPath,
  char* tooltip,
  ComponentName name,
  bool drawNow,
  bool isImageView
) {
  btns.push_back(new Button(pos.x + x, pos.y + y, w, h, btnStyle, imgPath, tooltip, name, drawNow, isImageView));
}

void Toolbar::addTextInput(
  int x,
  int y,
  int w,
  int h,
  const style_s* textInputStyle,
  char* tooltip,
  std::string value,
  ComponentName className
) {
  textInputs.push_back(new TextInput(pos.x + x, pos.y + y, w, h, textInputStyle, tooltip, value, className));
}

bool Toolbar::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
		for (size_t i = 0; i < btns.size(); i++)
      if (btns[i]->clicked(event)) break;

    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i]->clicked(event)) break;

    return true;
	}
  return false;
}

bool Toolbar::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
		for (size_t i = 0; i < btns.size(); i++)
      if (btns[i]->hovered(event)) return true;
    
    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i]->hovered(event)) return true;
    
    return true;
	}
  return false;
}

void Toolbar::draw(SDL_Surface * surf) {
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
}