#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "Button.hpp"
#include "Controller/Controller.hpp"
#include "main/utils.hpp"

Button::Button(
  int x,
  int y,
  int w,
  int h,
  const style_s* btnStyle,
  char* imgPath,
  char* tooltip,
  ComponentName className,
  bool drawNow
) : Input(x, y, w, h, btnStyle, tooltip, className) {
  img = imgPath;
  isHovered = isFocused = false;
  
  if (drawNow) this->draw();
}

Button::~Button() {
  SDL_FreeSurface(tmpForTooltip);
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

void Button::drawClicked() {
  Draw_Rect(screen, pos.x, pos.y, pos.w, pos.h, focusedColor);
  Draw_Rect(screen, pos.x + 1, pos.y + 1, pos.w - 2, pos.h - 2, focusedColor);
}

bool Button::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    Controller::getController()->clearHoveredObj();
    toggleFocusedDraw();
    Controller::getController()->changeFocus(this, false);
    Controller::getController()->chooseTool(name);
    return true;
	}
  return false;
}

void Button::toggleFocusedDraw() {
  if (isFocused) {
    draw();
  } else {
    drawClicked();
  }
  SDL_Flip(screen);
  isFocused = !isFocused;
}

bool Button::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (Controller::getController()->changeHover(this)) toggleHoveredDraw();
    return true;
	}
  return false;
}

void Button::toggleHoveredDraw() {
  if (isHovered) {
    SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), 100, 20};
    SDL_BlitSurface(tmpForTooltip, NULL, screen, &tooltipPos);
  } else {
   drawTooltip(); 
  }
  SDL_Flip(screen);
  isHovered = !isHovered;
}
