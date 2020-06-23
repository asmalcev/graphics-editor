#pragma once
#include "Interfaces/Input.hpp"
#include "Interfaces/Hovered.hpp"

class Confirm : public Input, public Hovered {
private:
  char * btnText;
public:
  Confirm(int,int,int,int,const style_s *);
	~Confirm() override;
	void draw();
	bool clicked(SDL_Event *);
	bool hovered(SDL_Event *);
	void toggleHoveredDraw() override;

};