#pragma once
#include <iostream>
#include "Interfaces/Input.hpp"
#include "Interfaces/Focused.hpp"
#include "Interfaces/Hovered.hpp"
#include "Interfaces/Observer.hpp"

class TextInput : public Input, public Focused, public Hovered, public Observer {
protected:
  std::string value;

public:
  TextInput(SDL_Surface*,int,int,int,int,const style_s*,char*,std::string,ComponentName,bool = true);
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
  void notify() override;

};