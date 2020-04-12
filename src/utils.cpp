#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "graphicsEditor.hpp"
#include "Window.hpp"
#include "utils.hpp"

void renderText(SDL_Surface* screen, SDL_Rect dst, char* message, int fontSize) {
  SDL_Surface* textSurface;
	TTF_Font* fnt;

  if (!(fnt = TTF_OpenFont("../public/Ubuntu.ttf", fontSize))) {
    return;
	}
	if ((textSurface = TTF_RenderUTF8_Blended(fnt, message, {3,169,244}))) {
		SDL_BlitSurface(textSurface, NULL, screen, &dst);
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
	}

  TTF_CloseFont(fnt);
}