#include <vector>
#include <SDL/SDL.h>
#include "window.hpp"
#include "observer.hpp"

#include <iostream>

void Observer::callClickedWindow(SDL_Event* event) {
	SDL_Rect position;
	for (size_t i = 0; i < windows.size(); i++) {
		std::cout << event->button.x << " " << event->button.y << std::endl;
	}
}

void Observer::addSubscriber(Window win) {
  windows.push_back(win);
}