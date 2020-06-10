#include "Controller.hpp"
#include "Model/DataModel.hpp"
#include "Tools/PencilInstrument.hpp"
#include "Tools/ErraserInstrument.hpp"
#include "Tools/LineInstrument.hpp"
#include "Tools/CircleInstrument.hpp"
#include "Tools/RectInstrument.hpp"

#include <iostream>

Controller::Controller() {
  hoveredObj       = nullptr;
  focusedObj       = nullptr;
  focusedTextInput = nullptr;
  choosenTool      = nullptr;
  mousePressed     = false;
  m_canvas         = nullptr;

  m_tools.push_back(new PencilInstrument());
  m_tools.push_back(new ErraserInstrument());
  m_tools.push_back(new LineInstrument());
  m_tools.push_back(new CircleInstrument());
  m_tools.push_back(new RectInstrument());
}

void Controller::changeFocus(Focused* newObj, bool isInput) {
  if (focusedObj != newObj) {
    if (focusedObj != nullptr) focusedObj->toggleFocusedDraw();
    focusedObj = newObj;
  } else {
    focusedObj = nullptr;
  }
  if (!isInput) focusedTextInput = nullptr;
}

bool Controller::changeHover(Hovered* newObj) {
  if (hoveredObj != newObj) {
    if (hoveredObj != nullptr) hoveredObj->toggleHoveredDraw();
    hoveredObj = newObj;
    return true;
  }
  return false;
}

void Controller::clearHoveredObj() {
  if (hoveredObj != nullptr) {
    hoveredObj->toggleHoveredDraw();
    hoveredObj = nullptr;
  }
}

void Controller::focusTextInput(TextInput* newObj) {
  if (focusedTextInput != newObj)
    focusedTextInput = newObj;
  else
    focusedTextInput = nullptr;
}

void Controller::clickColorInput(ColorInput* choosedColor) {
  DataModel::getData()->setChoosenColor(choosedColor->getColorValue());
}


bool Controller::waitingForInput() {
  return focusedTextInput != nullptr;
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
    case CircleClass:
      choosenTool = m_tools[3];
      break;
    case RectClass:
      choosenTool = m_tools[4];
      break;
    
    default:
      choosenTool = nullptr;
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

void Controller::setCanvas(Canvas * canvas) {
  if (m_canvas == nullptr) {
    m_canvas = canvas;
  }
}


void Controller::save(SDL_Surface * screen) {
  if (m_canvas != nullptr) {
    SDL_Rect bound = m_canvas->getBound();
    SDL_Surface * tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
      SDL_DOUBLEBUF, bound.w, bound.h, window_scrdepth,
      screen->format->Rmask, screen->format->Gmask,
      screen->format->Bmask, screen->format->Amask);
      SDL_BlitSurface(screen, &bound, tmp, NULL);
      SDL_SaveBMP(tmp, "../example.bmp");
    SDL_FreeSurface(tmp);
  }
}

Controller* Controller::m_controller = 0;
