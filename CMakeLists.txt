cmake_minimum_required(VERSION 3.5)

project(GraphicsEditor)

file(GLOB CPP_SOURCES 
  "src/main/*.cpp",
  "src/Controller/*.cpp",
  "src/Model/*.cpp",
  "src/View/*.cpp",
  "src/Tools/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL_draw-1.2.13/include")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})