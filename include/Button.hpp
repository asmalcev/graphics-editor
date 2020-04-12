#pragma once
#include "ClickClient.hpp"

class Button : public ClickClient {

protected:
	SDL_Rect pos;
	SDL_Surface* screen;
	const Style* style;
	char* img;

public:
	Button(SDL_Surface*,int,int,int,int,const Style*,char*);
	~Button();
	void draw();
	SDL_Rect getBound();
	bool clicked(SDL_Event*);

};