#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include "graphicsEditor.hpp"
#include "Model/DataModel.hpp"
#include "Controller/Controller.hpp"
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "View/MainWindow.hpp"
#include "View/Modal.hpp"
#include "utils.hpp"

/*

	export CFLAGS="`sdl-config --cflags` -I../../../libs/SDL_draw-1.2.13/include"
	export LIBS="`sdl-config --libs` ../../../libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a"
	g++ main/*.cpp Controller/*.cpp Model/*.cpp View/*.cpp Tools/*.cpp -Wall $CFLAGS $LIBS -lSDL -lSDL_ttf -lSDL_draw -I ./  && ./a.out && rm a.out
	
*/

class ColorInputData {
public:
	Uint32 color;
	char* value;
	ColorInputData(Uint32 colorValue, char* stringValue) {
		color = colorValue;
		value = stringValue;
	}
};

int main(int argc, char *argv[]) {
 	SDL_Surface* screen;
 	SDL_Event event;
	std::vector<ColorInputData> colors;
	colors.push_back(ColorInputData(0x212121, (char*) "#212121"));
	colors.push_back(ColorInputData(0x9E9E9E, (char*) "#9E9E9E"));
	colors.push_back(ColorInputData(0x795548, (char*) "#795548"));
	colors.push_back(ColorInputData(0xFF5722, (char*) "#FF5722"));
	colors.push_back(ColorInputData(0xFF9800, (char*) "#FF9800"));
	colors.push_back(ColorInputData(0xFFC107, (char*) "#FFC107"));
	colors.push_back(ColorInputData(0xFFEB3B, (char*) "#FFEB3B"));
	colors.push_back(ColorInputData(0xCDDC39, (char*) "#CDDC39"));
	colors.push_back(ColorInputData(0x8BC34A, (char*) "#8BC34A"));
	colors.push_back(ColorInputData(0x4CAF50, (char*) "#4CAF50"));
	colors.push_back(ColorInputData(0x009688, (char*) "#009688"));
	colors.push_back(ColorInputData(0x00BCD4, (char*) "#00BCD4"));
	colors.push_back(ColorInputData(0x03A9F4, (char*) "#03A9F4"));
	colors.push_back(ColorInputData(0x2196F3, (char*) "#2196F3"));
	colors.push_back(ColorInputData(0x3F51B5, (char*) "#3F51B5"));
	colors.push_back(ColorInputData(0x673AB7, (char*) "#673AB7"));
	colors.push_back(ColorInputData(0x9C27B0, (char*) "#9C27B0"));
	colors.push_back(ColorInputData(0xE91E63, (char*) "#E91E63"));
	colors.push_back(ColorInputData(0xF44336, (char*) "#F44336"));
	colors.push_back(ColorInputData(0xFFFFFF, (char*) "#FFFFFF"));
	colors.push_back(ColorInputData(0x000000, (char*) "#000000"));
	// colors.push_back(ColorInputData(0x, (char*) "#"));

 	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Can't init SDL" << std::endl;
		delete Controller::getController();
		return 1;
 	}
	if (TTF_Init()){
		std::cout << "Can't init TTF" << std::endl;
		delete Controller::getController();
 		return 1;
	}

 	screen = SDL_SetVideoMode(window_width, window_height, window_scrdepth, SDL_ANYFORMAT);
 	if (!screen) {
		std::cout << "Can't create screen surface" << std::endl;
		SDL_Quit();
		delete Controller::getController();
		return 1;
 	}

	MainWindow mainWindow(screen);
	mainWindow.getToolbar()->draw();
	mainWindow.getPalette()->draw();
	mainWindow.getCanvas()->draw();

	Controller::getController()->setCanvas(mainWindow.getCanvas());

	mainWindow.getToolbar()->addButton(
		0, 0, 32, 32, &btnStyle, (char*) "../public/pencil.bmp", (char*) "Pencil", ComponentName::PencilClass);
	mainWindow.getToolbar()->addButton(
		32, 0, 32, 32, &btnStyle, (char*) "../public/erraser.bmp", (char*) "Eraser", ComponentName::ErraserClass);
	mainWindow.getToolbar()->addButton(
		64, 0, 32, 32, &btnStyle, (char*) "../public/filler.bmp", (char*) "Filler", ComponentName::FillerClass);
	mainWindow.getToolbar()->addButton(
		96, 0, 32, 32, &btnStyle, (char*) "../public/circle.bmp", (char*) "Circle", ComponentName::CircleClass);
	mainWindow.getToolbar()->addButton(
		128, 0, 32, 32, &btnStyle, (char*) "../public/square.bmp", (char*) "Rect", ComponentName::RectClass);
	mainWindow.getToolbar()->addButton(
		160, 0, 32, 32, &btnStyle, (char*) "../public/line.bmp", (char*) "Line", ComponentName::LineClass);
	mainWindow.getToolbar()->addSaveButton(0, 32, 64, 32, &btnStyle);

	mainWindow.getToolbar()->addTextInput(
		96, 160, 36, 32, &textInputStyle, (char*) "Line width", std::to_string(DataModel::getData()->getLineWidth()), ComponentName::Line);

	mainWindow.getToolbar()->addText(
		12, 172, (char*) "Line width:", 16, 0x333333);
	mainWindow.getToolbar()->addText(
		140, 172, (char*) "px", 16, 0x333333);

	mainWindow.getPalette()->addText(
		12, 12, (char*) "Choosen color", 16, 0x333333);
	mainWindow.getPalette()->addText(
		12, 44, (char*) "Set RGB color", 16, 0x333333);
	mainWindow.getPalette()->addText(
		12, 108, (char*) "Color presets", 16, 0x333333);

	mainWindow.getPalette()->addTextInput(
		0, 64, 48, 32, &textInputStyle, (char*) "R value", std::to_string(DataModel::getData()->getRvalue()), ComponentName::R);
	mainWindow.getPalette()->addTextInput(
		48, 64, 48, 32, &textInputStyle, (char*) "G value", std::to_string(DataModel::getData()->getGvalue()), ComponentName::G);
	mainWindow.getPalette()->addTextInput(
		96, 64, 48, 32, &textInputStyle, (char*) "B value", std::to_string(DataModel::getData()->getBvalue()), ComponentName::B);

	mainWindow.getPalette()->setChoosenColor(160, 0, 32, 32, &colorInputStyle, 0xFFEB3B, (char*) "#FFEB3B", ComponentName::None);
	DataModel::getData()->addColorListener(mainWindow.getPalette()->getTextInput(0));
	DataModel::getData()->addColorListener(mainWindow.getPalette()->getTextInput(1));
	DataModel::getData()->addColorListener(mainWindow.getPalette()->getTextInput(2));
	DataModel::getData()->addColorListener(mainWindow.getPalette()->getChoosenColor());

	for (size_t i = 0; i < colors.size(); i++) {
		mainWindow.getPalette()->addColorInput((i % 6) * 32, 128 + (i / 6) * 32, 32, 32, &colorInputStyle, colors[i].color, colors[i].value, ComponentName::Color);
	}

	Modal mws(screen, 400, 200, &modalWindowStyle);
	mws.draw();

 	SDL_Flip(screen);
 	while(SDL_WaitEvent(&event)){
		switch (event.type) {
			case SDL_QUIT:
				TTF_Quit();
				SDL_Quit();
				delete Controller::getController();
 	   		return 0;
			case SDL_MOUSEBUTTONDOWN:
				Controller::getController()->changeMouseState(true);
				mainWindow.clicked(&event);
				break;
			case SDL_MOUSEBUTTONUP:
				Controller::getController()->changeMouseState(false);
				mainWindow.mouseUp(&event);
				break;
			case SDL_MOUSEMOTION:
				mainWindow.hovered(&event);
				break;
			case SDL_KEYDOWN:
				if (Controller::getController()->waitingForInput())
					Controller::getController()->readInput(&event);
				break;
		}

    // switch (event.key.keysym.sym) {
		// 	default:
		// 		break;
    // }
 	}

	TTF_Quit();
 	SDL_Quit();
	delete Controller::getController();
 	return 2;
}