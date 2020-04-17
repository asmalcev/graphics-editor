#include "DataModel.hpp"

DataModel::DataModel() {
  lineWidth = 2;
  choosenColor = 0xFFEB3B;
  Rvalue = 255;
  Gvalue = 235;
  Bvalue = 59;
  m_tool = NULL;
}

void DataModel::setLineWidth(int newValue) {
  lineWidth = newValue;
}

int DataModel::getLineWidth() {
  return lineWidth;
}

void DataModel::setChoosenColor(Uint32 newValue) {
  choosenColor = newValue;
}

Uint32 DataModel::getChoosenColor() {
  return choosenColor;
}

void DataModel::setRvalue(int newValue) {
  Rvalue = newValue;
}

void DataModel::setGvalue(int newValue) {
  Gvalue = newValue;
}

void DataModel::setBvalue(int newValue) {
  Bvalue = newValue;
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

void DataModel::chooseTool(Tool* newTool) {
  m_tool = newTool;
}

Tool* DataModel::getTool() {
  return m_tool;
}

DataModel* DataModel::m_dataModel = 0;