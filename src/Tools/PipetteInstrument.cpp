#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Model/DataModel.hpp"
#include "PipetteInstrument.hpp"
#include "main/graphicsEditor.hpp"

Uint32 getpixel(SDL_Surface * surface, int x, int y) {
  int bpp = surface->format->BytesPerPixel;
  Uint8 * p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *) p;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *) p;
    default:
      return 0;
  }
}

void PipetteInstrument::draw(SDL_Surface * screen, int x, int y, SDL_Rect bound) {
  pos.x = x;
  pos.y = y;
}

void PipetteInstrument::finishDraw(SDL_Surface * screen, SDL_Rect bound) {
  DataModel::getData()->setChoosenColor(getpixel(screen, pos.x, pos.y));
}
