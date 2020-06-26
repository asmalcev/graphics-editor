#pragma once
#include "main/graphicsEditor.hpp"
#include "ImageInstrument.hpp"

class OpenImageInstrument : public ImageInstrument {
  void finishDraw(SDL_Rect) override;
};