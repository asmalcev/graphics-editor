#pragma once
#include <vector>
#include <istream>
#include "graphicsEditor.hpp"
#include "Window.hpp"
#include "ColorInput.hpp"
#include "ChoosenColor.hpp"
#include "TextInput.hpp"

class Palette : public Window {
private:
  std::vector<ColorInput> colors;
  std::vector<TextInput> textInputs;
  ChoosenColor* m_choosenColor;

public:
  Palette(SDL_Surface*,int,int,int,int,const Style*);
  Palette();
  void draw() override;
	SDL_Rect getBound() override;
	bool clicked(SDL_Event*) override;
	bool hovered(SDL_Event*) override;
  void addColorInput(int,int,int,int,const Style*,Uint32,char*);
  void addTextInput(int,int,int,int,const Style*,char*,std::string);
  void setChoosenColor(int,int,int,int,const Style*,Uint32,char*);
  void setButton(int,int,int,int,const Style*,char*,char*);

};