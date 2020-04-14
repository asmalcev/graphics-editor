#pragma once
#include <SDL/SDL.h>
#include "Focused.hpp"
#include "Hovered.hpp"
#include "TextInput.hpp"

class Controller {
private:
  static Controller* controller;
  Focused* focusedObj;
  Hovered* hoveredObj;
  TextInput* focusedTextInput;
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
  void focusTextInput(TextInput*);
  bool waitingForInput();
  void readInput(SDL_Event*);

};
