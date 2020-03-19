#pragma once

class Observer {
protected:
  std::vector<Window> windows; 

public:
  Observer();
  ~Observer();
  void callClickedWindow(SDL_Event*);
  void addSubscriber(Window);
};