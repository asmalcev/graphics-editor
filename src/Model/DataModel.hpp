#pragma once
#include <SDL/SDL.h>
#include <vector>
#include "Interfaces/Observer.hpp"
#include <string>

class DataModel {
private:
  static DataModel * m_dataModel;
  DataModel();
  void notifyColorListeners();

  int lineWidth, Rvalue, Gvalue, Bvalue;
  std::vector<Observer *> colorListeners;
  std::string filePath;
  Uint32 choosenColor;
  SDL_Surface * canvasSurf;

public:
  static DataModel * getData() {
    if(!m_dataModel)           
      m_dataModel = new DataModel();
    return m_dataModel;
  }
  ~DataModel();

  void setLineWidth(int);
  int getLineWidth();
  void setChoosenColor(Uint32);
  Uint32 getChoosenColor();
  void setRvalue(int);
  void setGvalue(int);
  void setBvalue(int);
  int getRvalue();
  int getGvalue();
  int getBvalue();
  void addColorListener(Observer *);
  void setFilePath(std::string);
  std::string getFilePath();
  void setCanvasSurface(SDL_Surface *);
  SDL_Surface * getCanvasSurface();

};