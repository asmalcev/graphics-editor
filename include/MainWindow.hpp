#pragma once
#include <vector>

class MainWindow {
private:
  std::vector<Window*> windows;
  SDL_Surface* screen;

public:
  MainWindow(SDL_Surface*);
  ~MainWindow();
  void addWindow(Window*);
  void clicked(SDL_Event*);
  void hovered(SDL_Event*);
  void draw();
  Window* getWindow(size_t); 

};