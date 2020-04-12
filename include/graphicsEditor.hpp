#pragma once

typedef struct {
  Sint16 margin;
  Sint16 padding;
  Uint32 color;
  Uint16 shadowOffset;
  Uint32 shadowColor;
} Style;

extern const Uint32 mainColor;
extern const Uint32 backgroundColor;

extern const Uint16 window_width;
extern const Uint16 window_height;

extern const Style windowStyle;
extern const Style btnStyle;