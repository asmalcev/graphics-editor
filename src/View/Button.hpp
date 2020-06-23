#pragma once
#include "Interfaces/Input.hpp"
#include "Interfaces/Focused.hpp"
#include "Interfaces/Hovered.hpp"

class Button : public Input, public Focused, public Hovered {
private:
	char * img;

public:
	Button(int,int,int,int,const style_s*,char*,char*,ComponentName,bool=true);
	~Button() override;
	void draw();
	bool clicked(SDL_Event*);
	bool hovered(SDL_Event*);
	void drawClicked();
	void toggleFocusedDraw() override;
	void toggleHoveredDraw() override;

};