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

enum ComponentName {None, Line, R, G, B, Color};

constexpr Uint32 mainColor = 0xE8E8EC;
constexpr Uint32 backgroundColor = 0x2B2D42;
constexpr Uint32 focusedColor = 0xff1053;

constexpr Uint16 window_width = 1000;
constexpr Uint16 window_height = 600;
constexpr Uint16 window_scrdepth = 32;

constexpr style_s windowStyle = {12, mainColor, 4, 0x1E2036};
constexpr style_s btnStyle = {12, 0x1A237E, 2, 0x9E9E9E, 0xFFF59D, 0x212121, 16};
constexpr style_s textInputStyle = {12, 0x757575, 2, 0x9E9E9E, 0xFFF59D, 0x212121, 16};
constexpr style_s colorInputStyle = {12, 0x757575, 2, 0x9E9E9E, 0xFFF59D, 0x212121, 16};