#pragma once
#include <SDL/SDL.h>
#include "main/utils.hpp"

class Window {

protected:
	SDL_Rect pos;
	SDL_Surface * screen;
	const style_s * style;

public:
	virtual void draw() = 0;
	virtual SDL_Rect getBound() = 0;
	virtual bool clicked(SDL_Event *) = 0;
	virtual bool hovered(SDL_Event *) = 0;

	void addText(int x, int y, char * text, int fontSize, Uint32 color) {
		SDL_Rect textPos = {(Sint16) (pos.x + x),(Sint16) (pos.y + y), 0, 0};
		renderText(screen, textPos, text, fontSize, color);
	}
	
};