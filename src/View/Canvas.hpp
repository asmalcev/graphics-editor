#pragma once
#include "main/graphicsEditor.hpp"
#include "Interfaces/Window.hpp"

class Canvas : public Window {
public:
  Canvas(int,int,int,int,const style_s *);
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
	void draw(SDL_Surface *) override;
	bool mouseUp(SDL_Event *);
};