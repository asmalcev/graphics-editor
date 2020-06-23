#pragma once
#include "Canvas.hpp"
#include "Toolbar.hpp"
#include "Palette.hpp"

class MainWindow {
private:
  Canvas      * m_canvas;
  Toolbar     * m_toolbar;
  Palette     * m_palette;
  void createWindows();

public:
  MainWindow();
  ~MainWindow();
  void clicked(SDL_Event *);
  void hovered(SDL_Event *);
  void draw(SDL_Surface *);
  Canvas * getCanvas();
  Toolbar * getToolbar();
  Palette * getPalette();
  void mouseUp(SDL_Event *);

};