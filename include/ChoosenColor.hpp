#pragma once
#include "Input.hpp"
#include "Hovered.hpp"

class ChoosenColor : public Input, public Hovered {
protected:
  Uint32 colorValue;

public:
  ChoosenColor(SDL_Surface*,int,int,int,int,const style_s*,Uint32,char*);
  ChoosenColor() {};
  ~ChoosenColor() {};
  void draw() override;
  void toggleHoveredDraw() override;
  bool hovered(SDL_Event*);

};