#pragma once
#include <SDL/SDL.h>
#include "Interfaces/Focused.hpp"
#include "Interfaces/Hovered.hpp"
#include "View/TextInput.hpp"

class Controller {
private:
  static Controller* m_controller;
  Focused* focusedObj;
  Hovered* hoveredObj;
  TextInput* focusedTextInput;
  Uint32 choosedColor;
  Controller();

public:
  static Controller* getController() {
    if(!m_controller)           
      m_controller = new Controller();
    return m_controller;
  }
  
  void changeFocus(Focused*);
  bool changeHover(Hovered*);
  void clearHoveredObj();
  void focusTextInput(TextInput*);
  bool waitingForInput();
  void readInput(SDL_Event*);

};
