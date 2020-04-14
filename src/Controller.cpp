#include "Controller.hpp"

Controller::Controller() {
  hoveredObj = NULL;
  focusedObj = NULL;
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

Controller* Controller::controller = 0;
