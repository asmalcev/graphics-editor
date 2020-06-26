cmake_minimum_required(VERSION 3.5)

project(GraphicsEditor)

file(GLOB CPP_SOURCES 
  "src/main/*.cpp",
  "src/Controller/*.cpp",
  "src/Model/*.cpp",
  "src/View/*.cpp",
  "src/Tools/*.cpp"
)

# find_package(SDL1.2 REQUIRED)
# include_directories(${SDL1_2_INCLUDE_DIRS})

add_definitions(-Wall)
# add_definitions(`sdl-config --cflags` -I ../src/libs/SDL_draw-1.2.13/include `sdl-config --libs` ../src/libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL_draw-1.2.13/include")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})
# target_link_libraries(${PROJECT_NAME} ${SDL1_2_LIBRARIES})