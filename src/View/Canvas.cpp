#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "main/graphicsEditor.hpp"
#include "Controller/Controller.hpp"
#include "Canvas.hpp"

Canvas::Canvas(
  int x,
  int y,
  int w,
  int h,
  const style_s * windowStyle
) : Window(x, y, w, h, windowStyle) {}

bool Canvas::clicked(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    Tool * m_tool = Controller::getController()->getTool();
    if (m_tool != NULL) {
      m_tool->draw(event->button.x, event->button.y, pos);
    }
    return true;
	}
  return false;
}

bool Canvas::hovered(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (Controller::getController()->isMousePressed()) {
      Tool * m_tool = Controller::getController()->getTool();
      if (m_tool != NULL) {
        m_tool->draw(event->button.x, event->button.y, pos);
      }
    }
    return true;
	}
  return false;
}

bool Canvas::mouseUp(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    Tool * m_tool = Controller::getController()->getTool();
    if (m_tool != NULL) {
      m_tool->finishDraw(pos);
    }
    return true;
  }
  return false;
}

void Canvas::draw(SDL_Surface * surf) {
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