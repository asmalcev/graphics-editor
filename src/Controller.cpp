#include "Controller.hpp"

#include <iostream>

Controller::Controller() {
  hoveredObj = NULL;
  focusedObj = NULL;
  focusedTextInput = NULL;
}

void Controller::changeFocus(Focused* newObj) {
  if (focusedObj != newObj) {
    if (focusedObj != NULL) focusedObj->toggleFocusedDraw();
    focusedObj = newObj;
  } else {
    focusedObj = NULL;
  }
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

bool Controller::waitingForInput() {
  return focusedTextInput != NULL;
}

void Controller::readInput(SDL_Event* event) {
  SDLKey sym = event->key.keysym.sym;
  std::string value = focusedTextInput->getValue();
  size_t len = value.length();

  if (sym == SDLK_BACKSPACE && len > 0)
    value = value.substr(0, len - 1);

  if (sym >= 48 && sym <= 57 && len < 2)
    value += (char) sym;

  focusedTextInput->changeValue(value);
}


Controller* Controller::controller = 0;
