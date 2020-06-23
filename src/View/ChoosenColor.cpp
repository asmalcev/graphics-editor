#include "Controller/Controller.hpp"
#include "Model/DataModel.hpp"
#include "ChoosenColor.hpp"
#include "main/utils.hpp"

ChoosenColor::ChoosenColor(
  int x,
  int y,
  int w,
  int h,
  const style_s* inputStyle,
  Uint32 color,
  char* tooltip,
  ComponentName className
) : Input(x, y, w, h, inputStyle, tooltip, className) {
  isHovered = isFocused = false;
  colorValue = color;
  
  this->draw();
}

ChoosenColor::~ChoosenColor() {
  SDL_FreeSurface(tmpForTooltip);
};


void ChoosenColor::draw() {
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
  Draw_FillRect(screen, pos.x, pos.y, pos.w, pos.h, colorValue);
  Draw_Rect(screen, pos.x, pos.y, pos.w, pos.h, style->color);
}

bool ChoosenColor::hovered(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (Controller::getController()->changeHover(this)) toggleHoveredDraw();
    return true;
	}
  return false;
}

void ChoosenColor::toggleHoveredDraw() {
  if (isHovered) {
    SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), 100, 20};
    SDL_BlitSurface(tmpForTooltip, NULL, screen, &tooltipPos);
  } else {
   drawTooltip(); 
  }
  SDL_Flip(screen);
  isHovered = !isHovered;
}

void ChoosenColor::setChoosenColor(Uint32 newValue) {
  colorValue = newValue;
  SDL_Flip(screen);
}

void ChoosenColor::notify() {
  colorValue = DataModel::getData()->getChoosenColor();
  tooltipText = IntToHexChars(colorValue);

  draw();
  SDL_Flip(screen);
}