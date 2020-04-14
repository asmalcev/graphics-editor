#pragma once
#include <vector>
#include "Button.hpp"
#include "TextInput.hpp"

class Window {

protected:
	SDL_Rect pos;
	SDL_Surface* screen;
	const Style* style;
	std::vector<Button> btns;
	std::vector<TextInput> textInputs;

public:
	Window(SDL_Surface*,int,int,int,int,const Style*);
	Window() {}
	void draw();
	SDL_Rect getBound();
	void addButton(int,int,int,int,const Style*,char*,char*);
	void addTextInput(int,int,int,int,const Style*,char*);
	void addText(int,int,char*,int,Uint32);
	bool clicked(SDL_Event*);
	bool hovered(SDL_Event*);
	
};
