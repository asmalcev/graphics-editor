#pragma once
#include <SDL/SDL.h>
#include "main/utils.hpp"
#include "Interfaces/Window.hpp"
#include "View/TextInput.hpp"
#include "View/Confirm.hpp"

class Modal : public Window {
protected:
  SDL_Surface * tmp;
  TextInput * txtInput;
  Confirm * m_confirm;
public:
  Modal(SDL_Surface *,int,int,const style_s *);
  ~Modal();
  void draw() override;
  void close();
	SDL_Rect getBound() override;
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
  void setInput(int,int,int,int,char *,char *,ComponentName);
  void setConfirm(int,int,int,int);
};
