#pragma once

SDL_Color translate_color(Uint32);
void renderText(SDL_Surface *, SDL_Rect,const char*, int, Uint32);
char* IntToHexChars(int);
char* IntToChars(int);
Uint32 createRGB(int,int,int);
Uint32 getpixel(SDL_Surface *,int,int);