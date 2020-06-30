#include "Controller.hpp"
#include "Model/DataModel.hpp"
#include "Tools/PencilInstrument.hpp"
#include "Tools/ErraserInstrument.hpp"
#include "Tools/LineInstrument.hpp"
#include "Tools/CircleInstrument.hpp"
#include "Tools/RectInstrument.hpp"
#include "Tools/ClearInstrument.hpp"
#include "Tools/ImageInstrument.hpp"
#include "Tools/OpenImageInstrument.hpp"
#include "Tools/PipetteInstrument.hpp"
#include "Tools/FillerInstrument.hpp"

Controller::Controller() {
  hoveredObj       = nullptr;
  focusedObj       = nullptr;
  focusedTextInput = nullptr;
  choosenTool      = nullptr;
  mousePressed     = false;
  m_modal          = nullptr;

  m_tools.push_back(new PencilInstrument());
  m_tools.push_back(new ErraserInstrument());
  m_tools.push_back(new LineInstrument());
  m_tools.push_back(new CircleInstrument());
  m_tools.push_back(new RectInstrument());
  m_tools.push_back(new ClearInstrument());
  m_tools.push_back(new ImageInstrument());
  m_tools.push_back(new PipetteInstrument());
  m_tools.push_back(new FillerInstrument());
  m_tools.push_back(new OpenImageInstrument());
}

void Controller::changeFocus(Focused * newObj, bool isInput) {
  if (focusedObj != newObj) {
    if (focusedObj != nullptr) focusedObj->toggleFocusedDraw();
    focusedObj = newObj;
  } else {
    focusedObj = nullptr;
  }
  if (!isInput) focusedTextInput = nullptr;
}

bool Controller::changeHover(Hovered * newObj) {
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

void Controller::clearFocusedObj() {
  if (focusedObj != nullptr) {
    focusedObj->toggleFocusedDraw();
    focusedObj = nullptr;
  }
}

void Controller::focusTextInput(TextInput * newObj) {
  if (focusedTextInput != newObj)
    focusedTextInput = newObj;
  else
    focusedTextInput = nullptr;
}

void Controller::clickColorInput(ColorInput * choosedColor) {
  DataModel::getData()->setChoosenColor(choosedColor->getColorValue());
}


bool Controller::waitingForInput() {
  return focusedTextInput != nullptr;
}

void Controller::readInput(SDL_Event* event) {
  SDLKey sym = event->key.keysym.sym;
  if (focusedTextInput->getComponentName() == ComponentName::FilePath) {
    std::string value = focusedTextInput->getValue();
    if (sym == SDLK_BACKSPACE) {
      if (!value.empty()) value.pop_back();
    } else {
      if (isprint(sym)) {
        value += sym;
      }
    }
    DataModel::getData()->setFilePath(value);
    focusedTextInput->changeValue(value);
  } else {
    int value = std::stoi(focusedTextInput->getValue());

    if (sym == SDLK_DOWN) {
      if (value > 0) value--;
    } else if (sym == SDLK_UP) {
      value++;
    } else if (sym == SDLK_LEFT) {
      value = 0;
    } else if (sym == SDLK_RIGHT) {
      value = 256;
    } else if (sym == SDLK_BACKSPACE) {
      value /= 10;
    } else if (sym >= 48 && sym <= 57) {
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
}

void Controller::keyEvents(SDL_Event * event) {
  SDLKey sym = event->key.keysym.sym;
  switch (sym) {
  case SDLK_p:
    buttonClicked(ComponentName::PencilClass);
    break;
  case SDLK_f:
    buttonClicked(ComponentName::FillerClass);
    break;
  case SDLK_e:
    buttonClicked(ComponentName::ErraserClass);
    break;
  case SDLK_ESCAPE:
    buttonClicked(ComponentName::Cancel);
    break;
  case SDLK_r:
    buttonClicked(ComponentName::RectClass);
    break;
  case SDLK_l:
    buttonClicked(ComponentName::LineClass);
    break;
  case SDLK_c:
    buttonClicked(ComponentName::CircleClass);
    break;
  case SDLK_x:
    buttonClicked(ComponentName::ClearClass);
    break;
  case SDLK_v:
    buttonClicked(ComponentName::PipetteClass);
    break;
  case SDLK_i:
    buttonClicked(ComponentName::ImageClass);
    break;
  case SDLK_o:
    buttonClicked(ComponentName::OpenImageClass);
    break;
  case SDLK_s:
    buttonClicked(ComponentName::SaveClass);
    break;
  
  default:
    break;
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

void Controller::setCanvasParams(Canvas * canvas) {
  if (DataModel::getData()->getCanvasSurface() == nullptr) {
    SDL_Rect bound = canvas->getBound();
    SDL_Surface * surf = SDL_CreateRGBSurface(SDL_HWSURFACE |
      SDL_DOUBLEBUF, bound.w, bound.h, window_scrdepth,
      screen->format->Rmask, screen->format->Gmask,
      screen->format->Bmask, screen->format->Amask);
    SDL_BlitSurface(screen, &bound, surf, NULL);

    DataModel::getData()->setCanvasSurface(surf);
  }
}

void Controller::save() {
  SDL_Surface * surf = DataModel::getData()->getCanvasSurface();
  if (surf != nullptr) {
    SDL_SaveBMP(surf, DataModel::getData()->getFilePath().c_str());
  }
}

void Controller::openSaveModal() {
  if (openedModal == 1) {
    openedModal = 0;
    m_modal->close();
    SDL_Flip(screen);
  } else {
    if (m_modal != nullptr) {
      openedModal = 1;
      m_modal->setActionBtn(100, 90, 200, 40, (char *) "Save image", ComponentName::ConfirmSaving);
      m_modal->setCancelBtn(100, 130, 200, 40);
      m_modal->draw(screen);

      m_modal->addText(84, 12, (char*) "Input relative or absolute path", 18, 0x333333);
      m_modal->addText(84, 30, (char*) "with name and ends with .bmp", 18, 0x333333);
      SDL_Flip(screen);
    }
  }
}

void Controller::openImageModal() {
  if (openedModal == 2) {
    openedModal = 0;
    m_modal->close();
    SDL_Flip(screen);
  } else {
    if (m_modal != nullptr) {
      openedModal = 2;
      m_modal->setActionBtn(100, 90, 200, 40, (char *) "Open image", ComponentName::ConfirmOpening);
      m_modal->setCancelBtn(100, 130, 200, 40);
      m_modal->draw(screen);

      m_modal->addText(84, 12, (char*) "Input relative or absolute path", 18, 0x333333);
      m_modal->addText(84, 30, (char*) "with name and ends with .bmp", 18, 0x333333);
      SDL_Flip(screen);
    }
  }
}

void Controller::setModal(Modal * modal) {
  m_modal = modal;
}

int Controller::getIndexOfOpenedModal() {
  return openedModal;
}

void Controller::buttonClicked(ComponentName name) {
  clearHoveredObj();
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
    case ClearClass:
      choosenTool = m_tools[5];
      break;
    case ImageClass:
      clearFocusedObj();
      openImageModal();
      choosenTool = m_tools[6];
      break;
    case OpenImageClass:
      clearFocusedObj();
      openImageModal();
      choosenTool = m_tools[9];
      break;
    case PipetteClass:
      choosenTool = m_tools[7];
      break;
    case FillerClass:
      choosenTool = m_tools[8];
      break;
    case SaveClass:
      clearFocusedObj();
      openSaveModal();
      break;
    case ConfirmSaving:
      clearFocusedObj();
      openSaveModal();
      save();
      break;
    case ConfirmOpening:
      clearFocusedObj();
      openImageModal();
      break;
    case Cancel:
      clearFocusedObj();
      if (openedModal == 1) {
        openSaveModal();
      } else if (openedModal == 2) {
        openImageModal();
      }
      break;
    
    default:
      choosenTool = nullptr;
  }
}

Controller* Controller::m_controller = 0;
