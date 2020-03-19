cmake_minimum_required(VERSION 2.6)

project(GraphicsEditor)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-Wall `sdl-config --cflags` -I../../../libs/SDL_draw-1.2.13/include `sdl-config --libs` ../../../libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a -lSDL -lSDL_ttf -lSDL_draw)

file(GLOB CPPS "src/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/../../libs/SDL_draw-1.2.13/include")

add_executable(${PROJECT_NAME} ${CPPS})