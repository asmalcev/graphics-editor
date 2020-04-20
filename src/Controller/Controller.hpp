#pragma once
#include <SDL/SDL.h>
#include "Interfaces/Focused.hpp"
#include "Interfaces/Hovered.hpp"
#include "View/TextInput.hpp"
#include "View/ColorInput.hpp"
#include "Interfaces/Tool.hpp"

class Controller {
private:
  static Controller* m_controller;
  Focused* focusedObj;
  Hovered* hoveredObj;
  TextInput* focusedTextInput;
  Uint32 choosedColor;
  Tool* m_tool;
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
  void clickColorInput(ColorInput*);
  bool waitingForInput();
  void readInput(SDL_Event*);
  void chooseTool(Tool*);
  Tool* getTool();

};
