#pragma once
#include <SDL/SDL.h>
#include "Focused.hpp"
#include "Hovered.hpp"

class Controller {
private:
  static Controller* controller;
  Focused* focusedObj;
  Hovered* hoveredObj;
  Uint32 choosedColor;
  Controller();

public:
  static Controller* getController() {
    if(!controller)           
      controller = new Controller();
    return controller;
  }
  void changeFocus(Focused*);
  bool changeHover(Hovered*);
  void clearHoveredObj();

};
