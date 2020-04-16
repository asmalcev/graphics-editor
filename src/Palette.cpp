#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Palette.hpp"

Palette::Palette(
  SDL_Surface* screenSurface,
  int x,
  int y,
  int w,
  int h,
  const Style* windowStyle
) {
  style = windowStyle;
  screen = screenSurface;

  pos.x = x + style->margin;
  pos.y = y + style->margin;
  pos.w = w - style->margin;
  pos.h = h - style->margin;
  m_choosenColor = NULL;
}

void Palette::draw() {
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

SDL_Rect Palette::getBound() {
  return pos;
}

bool Palette::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    for (size_t i = 0; i < textInputs.size(); i++)
      if (textInputs[i].clicked(event)) break;

    for (size_t i = 0; i < colors.size(); i++)
      if (colors[i].clicked(event)) break;

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
      if (textInputs[i].hovered(event)) return true;

    for (size_t i = 0; i < colors.size(); i++)
      if (colors[i].hovered(event)) return true;
	}
  return false;
}

void Palette::addColorInput(
  int x,
  int y,
  int w,
  int h,
  const Style* colorStyle,
  Uint32 color,
  char* tooltip
) {
  colors.push_back(ColorInput(screen, pos.x + x, pos.y + y, w, h, colorStyle, color, tooltip));
}

void Palette::setChoosenColor(
  int x,
  int y,
  int w,
  int h,
  const Style* colorStyle,
  Uint32 color,
  char* tooltip
  ) {
  if (m_choosenColor != NULL) delete[] m_choosenColor;
  m_choosenColor = new ChoosenColor(screen, pos.x + x, pos.y + y, w, h, colorStyle, color, tooltip);
}

void Palette::addTextInput(
  int x,
  int y,
  int w,
  int h,
  const Style* textInputStyle,
  char* tooltip,
  std::string value
) {
  textInputs.push_back(TextInput(screen, pos.x + x, pos.y + y, w, h, textInputStyle, tooltip, value));
}