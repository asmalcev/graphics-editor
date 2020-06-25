#pragma once
#include <SDL/SDL.h>
#include "main/utils.hpp"
#include "Interfaces/Window.hpp"
#include "View/TextInput.hpp"
#include "View/Button.hpp"

class Modal : public Window {
protected:
  SDL_Surface * tmp;
  TextInput * txtInput;
  Button * actionBtn, * cancelBtn;
public:
  Modal(int,int,const style_s *);
  ~Modal();
  void draw(SDL_Surface *) override;
  void close();
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
  void setInput(int,int,int,int);
  void setActionBtn(int,int,int,int,char *,ComponentName);
  void setCancelBtn(int,int,int,int);
};
