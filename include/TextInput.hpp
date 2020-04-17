#pragma once
#include <iostream>
#include "Input.hpp"
#include "Focused.hpp"
#include "Hovered.hpp"

class TextInput : public Input, public Focused, public Hovered {
protected:
  std::string value;
  ValueClasses valueClass;

public:
  TextInput(SDL_Surface*,int,int,int,int,const style_s*,char*,std::string,ValueClasses);
  ~TextInput();
  void draw();
  SDL_Rect getBound();
	bool clicked(SDL_Event*);
	bool hovered(SDL_Event*);
	void drawClicked();
	void toggleFocusedDraw() override;
	void toggleHoveredDraw() override;
  void changeValue(std::string);
  std::string getValue();
  ValueClasses getValueClass();

};