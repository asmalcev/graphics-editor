#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Model/DataModel.hpp"
#include "OpenImageInstrument.hpp"
#include "main/utils.hpp"
#include <unistd.h>
#include <regex>

void OpenImageInstrument::finishDraw(SDL_Rect bound) {
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    std::string fileName = DataModel::getData()->getFilePath();
    std::cmatch m;
    std::regex e (".bmp$");
    if (
      access(fileName.c_str(), F_OK) != -1
      && std::regex_search(fileName.c_str(), m, e)
    ) {
      SDL_Surface * img = SDL_LoadBMP(fileName.c_str());

      SDL_Rect posFromTake = {0, 0, (Uint16) img->w, (Uint16) img->h};

      if (img->w > bound.w) {
        posFromTake.w -= img->w - bound.w;
      }

      if (img->h > bound.h) {
        posFromTake.h -= img->h- bound.h;
      }

      SDL_BlitSurface(img, &posFromTake, DataModel::getData()->getCanvasSurface(), NULL);
      updateCanvasScreen(&bound);
    }
  }
  pos.x = 0;
  pos.y = 0;
}
