#pragma once
#include <iostream>
#include "Input.hpp"
#include "Focused.hpp"
#include "Hovered.hpp"

class TextInput : public Input, public Focused, public Hovered {
protected:
  std::string value;

public:
  TextInput(SDL_Surface*,int,int,int,int,const Style*,char*);
  ~TextInput();
  void draw();
  SDL_Rect getBound();
	bool clicked(SDL_Event*);
	bool hovered(SDL_Event*);
	void drawClicked();
	void toggleFocusedDraw() override;
	void toggleHoveredDraw() override;
	void drawTooltip();
  void changeValue(std::string);
  std::string getValue();

};