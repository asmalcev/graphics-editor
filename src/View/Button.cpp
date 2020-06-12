#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "Button.hpp"
#include "Controller/Controller.hpp"
#include "main/utils.hpp"

Button::Button(
  SDL_Surface* screenSurface,
  int x,
  int y,
  int w,
  int h,
  const style_s* btnStyle,
  char* imgPath,
  char* tooltip,
  ComponentName className
) {
  screen = screenSurface;
  style = btnStyle;
  tooltipText = tooltip;
  name = className;

  pos.x = x + style->margin;
  pos.y = y + style->margin;
  pos.w = w - style->margin;
  pos.h = h - style->margin;
  
  TTF_SizeText(TTF_OpenFont("../public/Ubuntu.ttf", style->tooltipTextFontSize), tooltipText ,&textWidth, &textHeight);
  textHeight += 2;
  textWidth += 6;
  
  img = imgPath;
  isHovered = isFocused = false;
  
  tmpForTooltip = SDL_CreateRGBSurface(SDL_HWSURFACE |
    SDL_DOUBLEBUF, textWidth, textHeight, window_scrdepth,
    screen->format->Rmask, screen->format->Gmask,
    screen->format->Bmask, screen->format->Amask);
  this->draw();
}

Button::~Button() {}

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

SDL_Rect Button::getBound() {
  return pos;
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

void Button::drawTooltip() {
  SDL_Rect tooltipPos = {pos.x, (Sint16) (pos.y - textHeight - 1), (Uint16) textWidth, (Uint16) textHeight};
  SDL_BlitSurface(screen, &tooltipPos, tmpForTooltip, NULL);
  Draw_FillRect(screen,
    tooltipPos.x,
    tooltipPos.y,
    tooltipPos.w,
    tooltipPos.h, style->tooltipColor);
  Draw_Rect(screen,
    tooltipPos.x,
    tooltipPos.y,
    tooltipPos.w,
    tooltipPos.h, 0x333333);
  tooltipPos.x = (Sint16) (tooltipPos.x + 2);
  renderText(screen, tooltipPos, tooltipText, style->tooltipTextFontSize, style->tooltipTextColor);
}
