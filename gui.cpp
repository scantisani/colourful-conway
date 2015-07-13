#include <SDL2/SDL.h>
#include <iostream>
using std::cout; using std::endl;
using std::cerr;

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string; using std::to_string;

#include <vector>
using std::vector;

#include "gui.h"
#include "game.h"

Gui::Gui() {
	window = initWindow();
	renderer = initRenderer();
}

Gui::~Gui() {
	closeSDL();
}

void Gui::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		string sdl_error = SDL_GetError();
		throw runtime_error("SDL could not initialize! SDL Error: " + sdl_error);
	}
}

SDL_Window* Gui::initWindow() {
	SDL_Window* window = SDL_CreateWindow("Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == NULL) {
		string sdl_error = SDL_GetError();
		throw runtime_error("Window could not be created! SDL Error: " + sdl_error);
	}

	return window;
}

SDL_Renderer* Gui::initRenderer() {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		string sdl_error = SDL_GetError();
		throw runtime_error("Renderer could not be created! SDL Error: " + sdl_error);
	}

	return renderer;
}

void Gui::closeSDL() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

void Gui::drawGrid() {
	// Clear window/draw white background
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Draw black horizontal lines
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
	for (int i = 0; i < SCREEN_HEIGHT; i += CELL_SIZE)
		SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
	// Draw black vertical lines
	for (int i = 0; i < SCREEN_WIDTH; i += CELL_SIZE)
		SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
}

void Gui::fillCell(int x, int y) {
	SDL_Rect cell;
	// x and y are top left corner of cell mouse pointer is in
	cell.x = x - (x % CELL_SIZE) + 1; // 1-pixel buffer so as not to erase grid lines
	cell.y = y - (y % CELL_SIZE) + 1;
	cell.w = CELL_SIZE - 1;
	cell.h = CELL_SIZE - 1;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(renderer, &cell);
}

void Gui::drawFilledCells(vector<vector<int>> filledCells) {
	for (vector<int> cell : filledCells)
		fillCell(cell[0] * CELL_SIZE, cell[1] * CELL_SIZE);
}

void Gui::loop() {
	Game game(GRID_ROWS, GRID_COLUMNS);
	SDL_Event event;

	// While user hasn't closed the window
	while (event.type != SDL_QUIT) {
		drawGrid();

		// Poll for events on queue
		if (SDL_PollEvent(&event)) {
			if (event.button.type == SDL_MOUSEBUTTONDOWN) {
				game.toggleCell(event.button.x / CELL_SIZE, event.button.y / CELL_SIZE);
			}
		}

		drawFilledCells(game.getFilledCells());
		// Refresh window
		SDL_RenderPresent(renderer);
	}
}

int main(int argc, char const *argv[]) {
	try {
		Gui gui;
		gui.loop();
	} catch (runtime_error e) {
		cerr << e.what() << endl;
	}

	return 0;
}