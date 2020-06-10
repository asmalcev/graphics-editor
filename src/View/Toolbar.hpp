#pragma once
#include <iostream>
#include <vector>
#include "Interfaces/Window.hpp"
#include "Button.hpp"
#include "TextInput.hpp"
#include "Save.hpp"

class Toolbar : public Window {
private:
  std::vector<Button> btns;
	std::vector<TextInput> textInputs;
  Save * saveBtn;

public:
  Toolbar(SDL_Surface *,int,int,int,int,const style_s *);
  ~Toolbar();
  void addButton(int,int,int,int,const style_s *,char *,char *,ComponentName);
	void addTextInput(int,int,int,int,const style_s *,char *,std::string,ComponentName);
  void addSaveButton(int,int,int,int,const style_s *);
  void draw() override;
	SDL_Rect getBound() override;
	bool clicked(SDL_Event*) override;
	bool hovered(SDL_Event*) override;
	
};