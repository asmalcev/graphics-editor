#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "TextInput.hpp"
#include "Controller/Controller.hpp"
#include "Model/DataModel.hpp"
#include "main/utils.hpp"

TextInput::TextInput(
  int x,
  int y,
  int w,
  int h,
  const style_s* inputStyle,
  char* tooltip,
  std::string holderValue,
  ComponentName className,
  bool drawNow
) : Input(x, y, w, h, inputStyle, tooltip, className) {
  isHovered = isFocused = false;
  value = holderValue;

  if (drawNow) this->draw();
}

TextInput::~TextInput() {
  SDL_FreeSurface(tmpForTooltip);
}

void TextInput::draw() {
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
  Draw_FillRect(screen, pos.x, pos.y, pos.w, pos.h, mainColor);
  Draw_Rect(screen, pos.x, pos.y, pos.w, pos.h, style->color);
  SDL_Rect textPos = {(Sint16) (pos.x + 3), pos.y, pos.w, pos.h};
  renderText(screen, textPos, value.c_str(), 16, 0x333333);
}

void TextInput::drawClicked() {
  Draw_Rect(screen, pos.x, pos.y, pos.w, pos.h, focusedColor);
  Draw_Rect(screen, pos.x + 1, pos.y + 1, pos.w - 2, pos.h - 2, focusedColor);
}

bool TextInput::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    Controller::getController()->clearHoveredObj();
    toggleFocusedDraw();
    Controller::getController()->changeFocus(this, true);
    Controller::getController()->focusTextInput(this);
    return true;
	}
  return false;
}

void TextInput::toggleFocusedDraw() {
  if (isFocused) {
    draw();
  } else {
    drawClicked();
  }
  SDL_Flip(screen);
  isFocused = !isFocused;
}

bool TextInput::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (Controller::getController()->changeHover(this)) toggleHoveredDraw();
    return true;
	}
  return false;
}

void TextInput::toggleHoveredDraw() {
  if (isHovered) {
    SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), 100, 20};
    SDL_BlitSurface(tmpForTooltip, NULL, screen, &tooltipPos);
  } else {
    this->drawTooltip(); 
  }
  SDL_Flip(screen);
  isHovered = !isHovered;
}

void TextInput::changeValue(std::string newValue) {
  value = newValue;
  draw();
  drawClicked();
  SDL_Flip(screen);
}

std::string TextInput::getValue() {
  return value;
}

void TextInput::notify() {
  switch (name) {
    case ComponentName::Line:
      break;

    case ComponentName::R:
      value = IntToChars(DataModel::getData()->getRvalue());
      break;
    
    case ComponentName::G:
      value = IntToChars(DataModel::getData()->getGvalue());
      break;

    case ComponentName::B:
      value = IntToChars(DataModel::getData()->getBvalue());
      break;
    
    default:
      break;
  }
  draw();
}