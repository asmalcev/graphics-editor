#pragma once
#include <SDL/SDL.h>
#include "main/utils.hpp"
#include "Interfaces/Window.hpp"

class Modal : public Window {
protected:
  SDL_Surface * tmp;
  bool opened;
  TextInput * txtInput;
public:
  Modal(SDL_Surface *,int,int,const style_s *);
  ~Modal();
  void draw() override;
	SDL_Rect getBound() override;
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
};
