#pragma once
#include "Interfaces/Input.hpp"
#include "Interfaces/Hovered.hpp"

class Save : public Input, public Hovered {
private:
  char * btnText;
public:
  Save(int,int,int,int,const style_s *);
	~Save() override;
	void draw();
	bool clicked(SDL_Event *);
	bool hovered(SDL_Event *);
	void toggleHoveredDraw() override;
	
};