#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "graphicsEditor.hpp"
#include "Window.hpp"
#include "utils.hpp"

SDL_Color translate_color(Uint32 int_color) {
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		SDL_Color color={
			(Uint8) ((int_color & 0x00ff0000)/0x10000),
			(Uint8) ((int_color &0x0000ff00)/0x100),
			(Uint8) (int_color & 0x000000ff), 0};
	#else
		SDL_Color color={
			(Uint8) (int_color & 0x000000ff),
			(Uint8) ((int_color &0x0000ff00)/0x100),
			(Uint8) ((int_color & 0x00ff0000)/0x10000), 0};
	#endif
	return color;
}


void renderText(SDL_Surface* screen, SDL_Rect dst, const char* message, int fontSize, Uint32 color) {
  SDL_Surface* textSurface;
	TTF_Font* fnt;

  if (!(fnt = TTF_OpenFont("../public/Ubuntu.ttf", fontSize))) {
    return;
	}
	if ((textSurface = TTF_RenderUTF8_Blended(fnt, message, translate_color(color)))) {
		SDL_BlitSurface(textSurface, NULL, screen, &dst);
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
	}

  TTF_CloseFont(fnt);
}