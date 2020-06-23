#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <SDL/SDL_ttf.h>
#include "main/graphicsEditor.hpp"
#include "Controller/Controller.hpp"
#include "main/utils.hpp"
#include "ColorInput.hpp"

ColorInput::ColorInput(
  int x,
  int y,
  int w,
  int h,
  const style_s * inputStyle,
  Uint32 color,
  char * tooltip,
  ComponentName className
) : ChoosenColor(x, y, w, h, inputStyle, color, tooltip, className) {}

bool ColorInput::clicked(SDL_Event* event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    Controller::getController()->clearHoveredObj();
    toggleFocusedDraw();
    Controller::getController()->changeFocus(this, false);
    Controller::getController()->clickColorInput(this);
    return true;
	}
  return false;
}

void ColorInput::toggleFocusedDraw() {
  isFocused = !isFocused;
}

Uint32 ColorInput::getColorValue() {
  return colorValue;
}