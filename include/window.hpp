#pragma once

class Window {

protected:
	SDL_Rect pos;
	SDL_Surface* screen;

public:
	Window(SDL_Surface*,int,int,int,int,Uint32);
	Window() {}
	void draw(Uint32);
	SDL_Rect getBound();
	
};
