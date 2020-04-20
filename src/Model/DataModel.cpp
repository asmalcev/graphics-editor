#include "DataModel.hpp"
#include "main/utils.hpp"

DataModel::DataModel() {
  lineWidth = 2;
  choosenColor = 0xFFEB3B;
  Rvalue = 255;
  Gvalue = 235;
  Bvalue = 59;
}

void DataModel::setLineWidth(int newValue) {
  lineWidth = newValue;
}

int DataModel::getLineWidth() {
  return lineWidth;
}

void DataModel::setChoosenColor(Uint32 newValue) {
  choosenColor = newValue;
  SDL_Color color = translate_color(choosenColor);
  Rvalue = color.r;
  Gvalue = color.g;
  Bvalue = color.b;
  
  notifyColorListeners();
}

Uint32 DataModel::getChoosenColor() {
  return choosenColor;
}

void DataModel::setRvalue(int newValue) {
  Rvalue = newValue;
  choosenColor = createRGB(Rvalue, Gvalue, Bvalue);
  notifyColorListeners();
}

void DataModel::setGvalue(int newValue) {
  Gvalue = newValue;
  choosenColor = createRGB(Rvalue, Gvalue, Bvalue);
  notifyColorListeners();
}

void DataModel::setBvalue(int newValue) {
  Bvalue = newValue;
  choosenColor = createRGB(Rvalue, Gvalue, Bvalue);
  notifyColorListeners();
}

int DataModel::getRvalue() {
  return Rvalue;
}

int DataModel::getGvalue() {
  return Gvalue;
}

int DataModel::getBvalue() {
  return Bvalue;
}

void DataModel::addColorListener(Observer* newListener) {
  colorListeners.push_back(newListener);
}

void DataModel::notifyColorListeners() {
  for (unsigned i = 0; i < colorListeners.size(); i++) {
    colorListeners[i]->notify();
  }
}

DataModel* DataModel::m_dataModel = 0;