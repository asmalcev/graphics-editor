#pragma once
#include "Canvas.hpp"
#include "Toolbar.hpp"
#include "Palette.hpp"

class MainWindow {
private:
  SDL_Surface * screen;
  Canvas      * m_canvas;
  Toolbar     * m_toolbar;
  Palette     * m_palette;
  void createWindows();

public:
  MainWindow(SDL_Surface *);
  ~MainWindow();
  void clicked(SDL_Event *);
  void hovered(SDL_Event *);
  void draw();
  Canvas * getCanvas();
  Toolbar * getToolbar();
  Palette * getPalette();
  void mouseUp(SDL_Event *);

};