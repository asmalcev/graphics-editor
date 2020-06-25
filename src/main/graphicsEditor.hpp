#pragma once

struct style_s {
  Sint16 margin;
  Uint32 color;
  Uint16 shadowOffset;
  Uint32 shadowColor;
  Uint32 tooltipColor;
  Uint32 tooltipTextColor;
  int tooltipTextFontSize;
};

class Point {
public:
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
  Point(const Point & other) {
    x = other.x;
    y = other.y;
  }
};

enum ComponentName {
  None,
  Line,
  R, G, B,
  Color,
  PencilClass,
  ErraserClass,
  FillerClass,
  RectClass,
  CircleClass,
  LineClass,
  ClearClass,
  ImageClass,
  PipetteClass,
  SaveClass,
  FilePath,
  ConfirmSaving,
  ConfirmOpening,
  Cancel
};

constexpr Uint32 mainColor = 0xEDF2F4;
constexpr Uint32 backgroundColor = 0x1E2036;
constexpr Uint32 focusedColor = 0xFF1053;

constexpr Uint16 window_width = 1000;
constexpr Uint16 window_height = 600;
constexpr Uint16 window_scrdepth = 32;

constexpr style_s windowStyle = {12, mainColor, 4, 0x060620};
constexpr style_s btnStyle = {12, 0xB0BEC5, 2, 0xD3D5D4, 0xFFF59D, 0x212121, 16};
constexpr style_s textInputStyle = {12, 0x757575, 2, 0xD3D5D4, 0xFFF59D, 0x212121, 16};
constexpr style_s colorInputStyle = {12, 0x757575, 2, 0xD3D5D4, 0xFFF59D, 0x212121, 16};
constexpr style_s modalWindowStyle = {12, mainColor, 2, 0xD3D5D4, 0xFFF59D, 0x212121, 16};

extern SDL_Surface * screen;