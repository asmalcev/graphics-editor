#include <vector>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "graphicsEditor.hpp"
#include "MainWindow.hpp"
#include "Controller.hpp"

#include <iostream>

MainWindow::MainWindow(SDL_Surface* screenSurface) {
  screen = screenSurface;
	
	this->createWindows();
  this->draw();
}

MainWindow::~MainWindow() {

}

void MainWindow::createWindows() {
	m_canvas  = new Canvas(screen, 216, 0, 772, 588, &windowStyle);
	m_toolbar = new Toolbar(screen, 0, 0, 216, 216, &windowStyle);
	m_palette = new Palette(screen, 0, 216, 216, 372, &windowStyle);
	SDL_Flip(screen);
}

void MainWindow::clicked(SDL_Event* event) {
	if (m_canvas->clicked(event)) return;
	if (m_toolbar->clicked(event)) return;
	if (m_palette->clicked(event)) return;
}

void MainWindow::hovered(SDL_Event* event) {
	if (m_canvas->hovered(event)) return;
	if (m_toolbar->hovered(event)) return;
	if (m_palette->hovered(event)) return;
	Controller::getController()->clearHoveredObj();
}

void MainWindow::draw() {
  SDL_WM_SetCaption("GraphicsEditor", "GE");
	SDL_WM_SetIcon(SDL_LoadBMP("../public/GE.bmp"), NULL);
 	Draw_FillRect(screen, 0, 0, window_width, window_height, backgroundColor);
}

Canvas* MainWindow::getCanvas() {
	return m_canvas;
}

Toolbar* MainWindow::getToolbar() {
	return m_toolbar;
}

Palette* MainWindow::getPalette() {
	return m_palette;
}