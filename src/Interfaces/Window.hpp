#pragma once
#include <SDL/SDL.h>
#include "main/utils.hpp"
#include "main/graphicsEditor.hpp"

class Window {

protected:
	SDL_Rect pos;
	const style_s * style;

public:
	virtual bool clicked(SDL_Event *) = 0;
	virtual bool hovered(SDL_Event *) = 0;
	virtual void draw(SDL_Surface *) = 0;
  virtual ~Window() {};

	Window(
		int x,
		int y,
		int w,
		int h,
		const style_s * windowStyle
	) : style(windowStyle) {
		pos.x = x + style->margin;
		pos.y = y + style->margin;
		pos.w = w - style->margin;
		pos.h = h - style->margin;
	}

	SDL_Rect getBound() {
		return pos;
	}

	void addText(int x, int y, char * text, int fontSize, Uint32 color) {
		SDL_Rect textPos = {(Sint16) (pos.x + x),(Sint16) (pos.y + y), 0, 0};
		renderText(screen, textPos, text, fontSize, color);
	}
	
};