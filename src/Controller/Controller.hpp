#pragma once
#include <vector>
#include <SDL/SDL.h>
#include "Interfaces/Focused.hpp"
#include "Interfaces/Hovered.hpp"
#include "View/TextInput.hpp"
#include "View/ColorInput.hpp"
#include "Interfaces/Tool.hpp"
#include "View/Canvas.hpp"
#include "View/Modal.hpp"

class Controller {
private:
  static Controller * m_controller;
  Focused * focusedObj;
  Hovered * hoveredObj;
  TextInput * focusedTextInput;
  Uint32 choosedColor;
  Tool * choosenTool;
  Controller();
  std::vector<Tool *> m_tools;
  bool mousePressed;
  Canvas * m_canvas;
  std::vector<Modal *> m_modals;
  int openedModal;

public:
  static Controller* getController() {
    if(!m_controller)           
      m_controller = new Controller();
    return m_controller;
  }
  
  void changeFocus(Focused*,bool);
  bool changeHover(Hovered*);
  void clearHoveredObj();
  void focusTextInput(TextInput*);
  void clickColorInput(ColorInput*);
  bool waitingForInput();
  void readInput(SDL_Event*);
  void chooseTool(ComponentName);
  Tool* getTool();
  void changeMouseState(bool);
  bool isMousePressed();
  void save(SDL_Surface *);
  void openSaveModal(SDL_Surface *);
  void setCanvas(Canvas *);
  void addModal(Modal *);
  int getIndexOfOpenedModal();

};
