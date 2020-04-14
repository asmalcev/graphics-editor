#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "graphicsEditor.hpp"
#include "Controller.hpp"
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Window.hpp"
#include "MainWindow.hpp"
#include "utils.hpp"


/*
	export CFLAGS="`sdl-config --cflags` -I../../../libs/SDL_draw-1.2.13/include"
	export LIBS="`sdl-config --libs` ../../../libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a"
	g++ *.cpp -Wall $CFLAGS $LIBS -lSDL -lSDL_ttf -lSDL_draw -I ../include/ && ./a.out && rm a.out
*/

int main(int argc, char *argv[]) {
 	SDL_Surface* screen;
 	SDL_Event event;

 	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Can't init SDL" << std::endl;
		delete Controller::getController();
		return 1;
 	}
	if (TTF_Init()){
		std::cout << "Can't init TTF" << std::endl;
		delete Controller::getController();
 		return 1;
	}

 	screen = SDL_SetVideoMode(window_width, window_height, window_scrdepth, SDL_ANYFORMAT);
 	if (!screen) {
		std::cout << "Can't create screen surface" << std::endl;
		SDL_Quit();
		delete Controller::getController();
		return 1;
 	}

	MainWindow mainWindow(screen);


 	mainWindow.addWindow(new Window(screen, 0, 0, 216, 216, &windowStyle));
	mainWindow.getWindow(0)->addButton(0, 0, 32, 32, &btnStyle, (char*) "../public/pencil.bmp", (char*) "Pencil");
	mainWindow.getWindow(0)->addButton(32, 0, 32, 32, &btnStyle, (char*) "../public/erraser.bmp", (char*) "Eraser");
	mainWindow.getWindow(0)->addButton(64, 0, 32, 32, &btnStyle, (char*) "../public/filler.bmp", (char*) "Filler");
	mainWindow.getWindow(0)->addButton(96, 0, 32, 32, &btnStyle, (char*) "../public/circle.bmp", (char*) "Circle");
	mainWindow.getWindow(0)->addButton(128, 0, 32, 32, &btnStyle, (char*) "../public/square.bmp", (char*) "Square");
 	mainWindow.addWindow(new Window(screen, 0, 216, 216, 372, &windowStyle));
 	mainWindow.addWindow(new Window(screen, 216, 0, 772, 588, &windowStyle));

 	SDL_Flip(screen);
 	while(SDL_WaitEvent(&event)){
		switch (event.type) {
			case SDL_QUIT:
				TTF_Quit();
				SDL_Quit();
				delete Controller::getController();
 	   		return 0;
			case SDL_MOUSEBUTTONDOWN:
				mainWindow.clicked(&event);
				break;
			case SDL_MOUSEMOTION:
				mainWindow.hovered(&event);
				break;
		}

    switch (event.key.keysym.sym) {
			default:
				break;
    }
 	}

	TTF_Quit();
 	SDL_Quit();
	delete Controller::getController();
 	return 2;
}