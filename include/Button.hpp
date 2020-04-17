#pragma once
#include "Input.hpp"
#include "Focused.hpp"
#include "Hovered.hpp"

class Button : public Input, public Focused, public Hovered {
private:
	char* img;

public:
	Button(SDL_Surface*,int,int,int,int,const style_s*,char*,char*);
	~Button();
	void draw();
  SDL_Rect getBound();
	bool clicked(SDL_Event*);
	bool hovered(SDL_Event*);
	void drawClicked();
	void toggleFocusedDraw() override;
	void toggleHoveredDraw() override;
	void drawTooltip();

};