#pragma once

typedef struct {
  Sint16 margin;
  Sint16 padding;
  Uint32 color;
  Uint16 shadowOffset;
  Uint32 shadowColor;
  Uint32 tooltipColor;
  Uint32 tooltipTextColor;
  int tooltipTextFontSize;
} Style;

extern const Uint32 mainColor;
extern const Uint32 backgroundColor;
extern const Uint32 focusedColor;

extern const Uint16 window_width;
extern const Uint16 window_height;
extern const Uint16 window_scrdepth;

extern const Style windowStyle;
extern const Style btnStyle;
extern const Style textInputStyle;