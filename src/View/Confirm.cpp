#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "Confirm.hpp"
#include "Controller/Controller.hpp"
#include "main/utils.hpp"

Confirm::Confirm(
  int x,
  int y,
  int w,
  int h,
  const style_s * btnStyle
) : Input(x, y, w, h, btnStyle, (char *) "Confirm saving", ComponentName::SaveClass) {
  isHovered = false;
  btnText = (char *) "Confirm";
}

Confirm::~Confirm() {
  SDL_FreeSurface(tmpForTooltip);
}

void Confirm::draw() {
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
  SDL_Rect textPos = {(Sint16) (pos.x + 10), pos.y, pos.w, pos.h};
  renderText(screen, textPos, btnText, style->tooltipTextFontSize, style->tooltipTextColor);
}

bool Confirm::clicked(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    Controller::getController()->clearHoveredObj();
    Controller::getController()->openSaveModal();
    Controller::getController()->save();
    return true;
	}
  return false;
}

bool Confirm::hovered(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (Controller::getController()->changeHover(this)) toggleHoveredDraw();
    return true;
	}
  return false;
}

void Confirm::toggleHoveredDraw() {
  if (isHovered) {
    SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), 100, 20};
    SDL_BlitSurface(tmpForTooltip, NULL, screen, &tooltipPos);
  } else {
   drawTooltip(); 
  }
  SDL_Flip(screen);
  isHovered = !isHovered;
}