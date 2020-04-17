#pragma once
#include "main/graphicsEditor.hpp"
#include "Interfaces/Window.hpp"

class Canvas : public Window {
private:

public:
  Canvas(SDL_Surface*,int,int,int,int,const style_s*);
  void draw() override;
	SDL_Rect getBound() override;
	bool clicked(SDL_Event*) override;
	bool hovered(SDL_Event*) override;
};