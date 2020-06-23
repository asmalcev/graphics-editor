#pragma once
#include "Interfaces/Input.hpp"
#include "Interfaces/Hovered.hpp"
#include "Interfaces/Observer.hpp"

class ChoosenColor : public Input, public Hovered, public Observer {
protected:
  Uint32 colorValue;

public:
  ChoosenColor(int,int,int,int,const style_s *,Uint32,char *,ComponentName);
  ~ChoosenColor() override;
  void draw() override;
  void toggleHoveredDraw() override;
  bool hovered(SDL_Event *);
  void setChoosenColor(Uint32);
  void notify() override;

};