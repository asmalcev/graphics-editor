#pragma once
#include <vector>
#include <istream>
#include "main/graphicsEditor.hpp"
#include "Interfaces/Window.hpp"
#include "ColorInput.hpp"
#include "ChoosenColor.hpp"
#include "TextInput.hpp"

class Palette : public Window {
private:
  std::vector<ColorInput> colors;
  std::vector<TextInput> textInputs;
  ChoosenColor* m_choosenColor;

public:
  Palette(SDL_Surface*,int,int,int,int,const style_s*);
  Palette();
  void draw() override;
	SDL_Rect getBound() override;
	bool clicked(SDL_Event*) override;
	bool hovered(SDL_Event*) override;
  void addColorInput(int,int,int,int,const style_s*,Uint32,char*);
  void addTextInput(int,int,int,int,const style_s*,char*,std::string,ValueClasses);
  void setChoosenColor(int,int,int,int,const style_s*,Uint32,char*);
  void setButton(int,int,int,int,const style_s*,char*,char*);

};