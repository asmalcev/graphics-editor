#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "graphicsEditor.hpp"
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
		return 1;
 	}
	if (TTF_Init()){
		std::cout << "Can't init TTF" << std::endl;
 		return 1;
	}

 	screen = SDL_SetVideoMode(window_width, window_height, 32, SDL_ANYFORMAT);
 	if (!screen) {
		std::cout << "Can't create screen surface" << std::endl;
		SDL_Quit();
		return 1;
 	}

	MainWindow mainWindow(screen);


 	mainWindow.addWindow(new Window(screen, 0, 0, 216, 216, &windowStyle));
	mainWindow.getWindow(0)->addButton(0, 0, 32, 32, &btnStyle, (char*) "../public/pencil.bmp");
	mainWindow.getWindow(0)->addButton(32, 0, 32, 32, &btnStyle, (char*) "../public/erraser.bmp");
	mainWindow.getWindow(0)->addButton(64, 0, 32, 32, &btnStyle, (char*) "../public/filler.bmp");
	mainWindow.getWindow(0)->addButton(96, 0, 32, 32, &btnStyle, (char*) "../public/circle.bmp");
	mainWindow.getWindow(0)->addButton(128, 0, 32, 32, &btnStyle, (char*) "../public/square.bmp");
 	mainWindow.addWindow(new Window(screen, 0, 216, 216, 372, &windowStyle));
 	mainWindow.addWindow(new Window(screen, 216, 0, 772, 588, &windowStyle));

 	SDL_Flip(screen);
 	while(SDL_WaitEvent(&event)){
		switch (event.type) {
			case SDL_QUIT:
				TTF_Quit();
				SDL_Quit();
 	   		return 0;
			case SDL_MOUSEBUTTONDOWN:
				mainWindow.clicked(&event);
				break;
			case SDL_MOUSEMOTION:
				// mainWindow
				break;
		}

    switch (event.key.keysym.sym) {
			default:
				break;
    }
 	}

	TTF_Quit();
 	SDL_Quit();
 	return 2;
}