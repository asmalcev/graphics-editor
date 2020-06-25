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
  Tool * choosenTool;
  Canvas * m_canvas;
  Modal * m_modal;
  std::vector<Tool *> m_tools;
  int openedModal;
  bool mousePressed;

  Controller();

public:
  static Controller* getController() {
    if(!m_controller)           
      m_controller = new Controller();
    return m_controller;
  }
  
  // Focus control
  void changeFocus(Focused*,bool=false);
  void clearFocusedObj();
  void focusTextInput(TextInput*);
  
  // Hover control
  bool changeHover(Hovered*);
  void clearHoveredObj();

  // User input
  void clickColorInput(ColorInput*);
  bool waitingForInput();
  void readInput(SDL_Event*);

  // Modal control
  void setModal(Modal *);
  void save();
  void openSaveModal();
  void openImageModal();
  int getIndexOfOpenedModal();

  // Other
  Tool* getTool();
  void changeMouseState(bool);
  bool isMousePressed();
  void setCanvas(Canvas *);
  void buttonClicked(ComponentName);

};
