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
  Modal(int,int,const style_s *);
  ~Modal();
  void draw(SDL_Surface *) override;
  void close();
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
  void setInput(int,int,int,int,char *,char *,ComponentName);
  void setConfirm(int,int,int,int);
};
