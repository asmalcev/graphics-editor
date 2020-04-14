#include <SDL/SDL.h>
#include "graphicsEditor.hpp"

const Uint32 mainColor = 0xFFFFFF;
const Uint32 backgroundColor = 0x455A64;
const Uint32 focusedColor = 0x263238;

const Uint16 window_width = 1000;
const Uint16 window_height = 600;
const Uint16 window_scrdepth = 32;

const Style windowStyle = {12, 12, mainColor, 4, 0x37474f};
const Style btnStyle = {12, 0, 0x263238, 2, 0x9E9E9E, 0xFFF59D, 0x212121, 16};
const Style textInputStyle = {12, 0, 0x757575, 2, 0x9E9E9E, 0xFFF59D, 0x212121, 16};