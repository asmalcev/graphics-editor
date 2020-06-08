#include "Controller.hpp"
#include "Model/DataModel.hpp"
#include "Tools/PencilInstrument.hpp"
#include "Tools/ErraserInstrument.hpp"
#include "Tools/LineInstrument.hpp"

#include <iostream>

Controller::Controller() {
  hoveredObj = NULL;
  focusedObj = NULL;
  focusedTextInput = NULL;
  choosenTool = NULL;
  mousePressed = false;

  m_tools.push_back(new PencilInstrument());
  m_tools.push_back(new ErraserInstrument());
  m_tools.push_back(new LineInstrument());
}

void Controller::changeFocus(Focused* newObj, bool isInput) {
  if (focusedObj != newObj) {
    if (focusedObj != NULL) focusedObj->toggleFocusedDraw();
    focusedObj = newObj;
  } else {
    focusedObj = NULL;
  }
  if (!isInput) focusedTextInput = NULL;
}

bool Controller::changeHover(Hovered* newObj) {
  if (hoveredObj != newObj) {
    if (hoveredObj != NULL) hoveredObj->toggleHoveredDraw();
    hoveredObj = newObj;
    return true;
  }
  return false;
}

void Controller::clearHoveredObj() {
  if (hoveredObj != NULL) {
    hoveredObj->toggleHoveredDraw();
    hoveredObj = NULL;
  }
}

void Controller::focusTextInput(TextInput* newObj) {
  if (focusedTextInput != newObj)
    focusedTextInput = newObj;
  else
    focusedTextInput = NULL;
}

void Controller::clickColorInput(ColorInput* choosedColor) {
  DataModel::getData()->setChoosenColor(choosedColor->getColorValue());
}


bool Controller::waitingForInput() {
  return focusedTextInput != NULL;
}

void Controller::readInput(SDL_Event* event) {
  SDLKey sym = event->key.keysym.sym;
  int value = std::stoi(focusedTextInput->getValue());

  if (sym == SDLK_BACKSPACE) {
    value /= 10;
  }

  if (sym >= 48 && sym <= 57) {
    value = value * 10 + sym - 48;
  }

  switch (focusedTextInput->getComponentName()) {
    case ComponentName::Line:
      if (value > 20) value = 20;
      DataModel::getData()->setLineWidth(value);
      break;

    case ComponentName::R:
      if (value > 255) value = 255;
      DataModel::getData()->setRvalue(value);
      break;
    
    case ComponentName::G:
      if (value > 255) value = 255;
      DataModel::getData()->setGvalue(value);
      break;

    case ComponentName::B:
      if (value > 255) value = 255;
      DataModel::getData()->setBvalue(value);
      break;
    
    default:
      break;
  }

  focusedTextInput->changeValue(std::to_string(value));
}

void Controller::chooseTool(ComponentName name) {
  switch (name) {
    case PencilClass:
      choosenTool = m_tools[0];
      break;
    case ErraserClass:
      choosenTool = m_tools[1];
      break;
    case LineClass:
      choosenTool = m_tools[2];
      break;
    
    default:
      choosenTool = NULL;
  }
}

Tool* Controller::getTool() {
  return choosenTool;
}

void Controller::changeMouseState(bool state) {
  mousePressed = state;
}

bool Controller::isMousePressed() {
  return mousePressed;
}

Controller* Controller::m_controller = 0;
