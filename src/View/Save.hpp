#pragma once
#include "Interfaces/Input.hpp"
#include "Interfaces/Hovered.hpp"

class Save : public Input, public Hovered {
private:
  char * btnText;
public:
  Save(SDL_Surface *,int,int,int,int,const style_s *);
	~Save();
	void draw();
  SDL_Rect getBound();
	bool clicked(SDL_Event *);
	bool hovered(SDL_Event *);
	void toggleHoveredDraw() override;
	void drawTooltip();
};