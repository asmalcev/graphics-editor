#include <vector>
#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "main/graphicsEditor.hpp"
#include "MainWindow.hpp"
#include "Controller/Controller.hpp"

MainWindow::MainWindow() {
	m_canvas = nullptr;
	m_toolbar = nullptr;
	m_palette = nullptr;
	this->createWindows();
}

MainWindow::~MainWindow() {
	delete m_canvas;
	delete m_toolbar;
	delete m_palette;
}

void MainWindow::createWindows() {
	m_canvas  = new Canvas(216, 0, 772, 588, &windowStyle);
	m_toolbar = new Toolbar(0, 0, 216, 216, &windowStyle);
	m_palette = new Palette(0, 216, 216, 372, &windowStyle);
	SDL_Flip(screen);
}

void MainWindow::clicked(SDL_Event * event) {
	if (m_canvas->clicked(event)) return;
	if (m_toolbar->clicked(event)) return;
	if (m_palette->clicked(event)) return;
	Controller::getController()->clearFocusedObj();
}

void MainWindow::hovered(SDL_Event * event) {
	if (m_canvas->hovered(event)) return;
	if (m_toolbar->hovered(event)) return;
	if (m_palette->hovered(event)) return;
	Controller::getController()->clearHoveredObj();
}

void MainWindow::draw(SDL_Surface * surf) {
  SDL_WM_SetCaption("GraphicsEditor", "GE");
	SDL_WM_SetIcon(SDL_LoadBMP("../public/GE.bmp"), NULL);
 	Draw_FillRect(surf, 0, 0, window_width, window_height, backgroundColor);
	if (m_canvas != nullptr) m_canvas->draw(surf);
	if (m_toolbar != nullptr) m_toolbar->draw(surf);
	if (m_palette != nullptr) m_palette->draw(surf);
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

void MainWindow::mouseUp(SDL_Event * event) {
	m_canvas->mouseUp(event);
}
