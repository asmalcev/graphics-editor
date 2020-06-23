#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Palette.hpp"

Palette::Palette(
  int x,
  int y,
  int w,
  int h,
  const style_s* windowStyle
) : Window(x, y, w, h, windowStyle) {
  m_choosenColor = nullptr;
}

Palette::~Palette() {
  delete m_choosenColor;
  for (auto it = textInputs.begin(); it != textInputs.end(); it++) delete *it;
  for (auto it = colors.begin(); it != colors.end(); it++) delete *it;
}

bool Palette::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i]->clicked(event)) break;

    for (size_t i = 0; i < colors.size(); i++)
      if (colors[i]->clicked(event)) break;

    return true;
	}
  return false;
}

bool Palette::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (m_choosenColor->hovered(event)) return true;

    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i]->hovered(event)) return true;

    for (size_t i = 0; i < colors.size(); i++)
      if (colors[i]->hovered(event)) return true;
	}
  return false;
}

void Palette::addColorInput(
  int x,
  int y,
  int w,
  int h,
  const style_s * colorStyle,
  Uint32 color,
  char * tooltip,
  ComponentName name
) {
  colors.push_back(new ColorInput(pos.x + x, pos.y + y, w, h, colorStyle, color, tooltip, name));
}

void Palette::setChoosenColor(
  int x,
  int y,
  int w,
  int h,
  const style_s * colorStyle,
  Uint32 color,
  char * tooltip,
  ComponentName name
  ) {
  if (m_choosenColor != nullptr) delete[] m_choosenColor;
  m_choosenColor = new ChoosenColor(pos.x + x, pos.y + y, w, h, colorStyle, color, tooltip, name);
}

ChoosenColor* Palette::getChoosenColor() {
  return m_choosenColor;
}

void Palette::addTextInput(
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

TextInput* Palette::getTextInput(size_t index) {
  return textInputs[index];
}

void Palette::draw(SDL_Surface * surf) {
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