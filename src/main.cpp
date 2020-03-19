#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include "graphicsEditor.hpp"
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "window.hpp"
#include "observer.hpp"
#include "utils.hpp"
#include "button.hpp"


/*
	export CFLAGS="`sdl-config --cflags` -I../../../libs/SDL_draw-1.2.13/include"
	export LIBS="`sdl-config --libs` ../../../libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a"
	g++ *.cpp -Wall $CFLAGS $LIBS -lSDL -lSDL_ttf -lSDL_draw -I ../include/ && ./a.out && rm a.out
*/

int main(int argc, char *argv[]) {
 	SDL_Surface* screen;
 	SDL_Event event;
	Observer obs;

 	if (SDL_Init(SDL_INIT_VIDEO)) {
		return 1;
 	}
	if (TTF_Init())
 		return 1;

 	screen = SDL_SetVideoMode(window_width, window_height, 32, SDL_ANYFORMAT);
 	if (!screen) {
		SDL_Quit();
		return 1;
 	}
	SDL_WM_SetCaption("GraphicsEditor", "GE");
	SDL_WM_SetIcon(SDL_LoadBMP("../public/GE.bmp"), NULL);
 	Draw_FillRect(screen, 0, 0, window_width, window_height, backgroundColor);

 	obs.addSubscriber(Window(screen, 12, 12, 224, 224, mainColor));
 	obs.addSubscriber(Window(screen, 12, 248, 224, 340, mainColor));
 	obs.addSubscriber(Window(screen, 248, 12, 740, 576, mainColor));
	// Button Bush(screen, 80, 80, 80, 40, SDL_MapRGB(screen->format, 0,0,0), "btn");

 	SDL_Flip(screen);
 	while(SDL_WaitEvent(&event)){
		switch (event.type) {
			case SDL_QUIT:
				TTF_Quit();
				SDL_Quit();
 	   		return 0;
			case SDL_MOUSEBUTTONDOWN:
				obs.callClickedWindow(&event);
				break;
		}

    switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				TTF_Quit();
    		SDL_Quit();
    		return 0;

			default:
				break;
    }
 	}

	TTF_Quit();
 	SDL_Quit();
 	return 2;
}