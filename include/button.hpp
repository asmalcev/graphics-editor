#pragma once

class Button: public Window {

public:
	Button(SDL_Surface*,int,int,int,int,Uint32,char*);
	void draw(Uint32);
};