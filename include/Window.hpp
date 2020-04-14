#pragma once
#include <vector>
#include "Button.hpp"

class Window {

protected:
	SDL_Rect pos;
	SDL_Surface* screen;
	const Style* style;
	std::vector<Button> btns;

public:
	Window(SDL_Surface*,int,int,int,int,const Style*);
	Window() {}
	void draw();
	SDL_Rect getBound();
	void addButton(int,int,int,int,const Style*,char*,char*);
	bool clicked(SDL_Event*);
	bool hovered(SDL_Event*);
	
};
