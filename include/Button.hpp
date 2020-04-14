#pragma once
#include "Focused.hpp"
#include "Hovered.hpp"

class Button : public Focused, public Hovered {

protected:
	SDL_Rect pos;
	SDL_Surface* screen, *tmpForTooltip;
	const Style* style;
	char* img, *tooltipText;
	bool isFocused, isHovered;
	int textWidth, textHeight;

public:
	Button(SDL_Surface*,int,int,int,int,const Style*,char*,char*);
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