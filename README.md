# ![GE](public/GE.bmp) graphics-editor
###### 1st course work
## Dependencies
1. SDL 1.2 ([Download link](https://www.libsdl.org/download-1.2.php))
2. SDL_ttf 2.0 ([Download link](https://www.libsdl.org/projects/SDL_ttf/))
3. SDL_draw 1.2.13 ([Download link](http://sdl-draw.sourceforge.net/))
#### For Ubuntu users
1\) and 2) items can be done with next commands:
```
sudo apt install libsdl1.2-dev
sudo apt install libsdl-ttf2.0-dev 
```
## Installation guide
Now CMakeLists.txt isn't working :(
But there is another way to compile and run:
1. Add environment variable
```
export CFLAGS="`sdl-config --cflags` -Ilibs/SDL_draw-1.2.13/include"
export LIBS="`sdl-config --libs` libs/SDL_draw-1.2.13/src/libs/SDL_draw-1.2.13/include/SDL_draw.h"
```
2. Then compile all files
```
g++ main/*.cpp Controller/*.cpp Model/*.cpp View/*.cpp Tools/*.cpp -Wall $CFLAGS $LIBS -lSDL -lSDL_ttf -lSDL_draw -I ./ -o GraphicsEditor
```
3. And then run
```
./GraphicsEditor
```