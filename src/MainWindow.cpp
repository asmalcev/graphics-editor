#include <vector>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "graphicsEditor.hpp"
#include "Window.hpp"
#include "MainWindow.hpp"
#include "Controller.hpp"

#include <iostream>

MainWindow::MainWindow(SDL_Surface* screenSurface) {
  screen = screenSurface;

  this->draw();
}

MainWindow::~MainWindow() {
  windows.clear();
}

void MainWindow::clicked(SDL_Event* event) {
	for (size_t i = 0; i < windows.size(); i++) {
		if (windows[i]->clicked(event)) return;
	}
}

void MainWindow::hovered(SDL_Event* event) {
	for (size_t i = 0; i < windows.size(); i++) {
		if (windows[i]->hovered(event)) return;
	}
	Controller::getController()->clearHoveredObj();
}

void MainWindow::draw() {
  SDL_WM_SetCaption("GraphicsEditor", "GE");
	SDL_WM_SetIcon(SDL_LoadBMP("../public/GE.bmp"), NULL);
 	Draw_FillRect(screen, 0, 0, window_width, window_height, backgroundColor);
}

void MainWindow::addWindow(Window* window) {
  windows.push_back(window);
};

Window* MainWindow::getWindow(size_t index) {
	return windows[index];
}