#include <SDL2/SDL.h>

#include <chrono>
using std::chrono::time_point; using std::chrono::system_clock;
using std::chrono::milliseconds;

#include <iostream>
using std::cout; using std::endl;
using std::cerr;

#include <map>
using std::map;

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

	nextStepDue = system_clock::now();
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
	SDL_Window* window = SDL_CreateWindow("Colourful Conway", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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

void Gui::drawGame(Game game) {
	// Clear window/draw white background
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	drawFilledCells(game.getLiveCells());
	drawGrid();

	// Refresh window
	SDL_RenderPresent(renderer);
}

void Gui::drawGrid() {
	// Draw black horizontal lines
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
	for (int i = 0; i < SCREEN_HEIGHT; i += CELL_SIZE)
		SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
	// Draw black vertical lines
	for (int i = 0; i < SCREEN_WIDTH; i += CELL_SIZE)
		SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
}

void Gui::fillCell(map<char, int> cell) {
	SDL_Rect gridCell;

	gridCell.x = cell['x'] * CELL_SIZE;
	gridCell.y = cell['y'] * CELL_SIZE;
	gridCell.w = CELL_SIZE;
	gridCell.h = CELL_SIZE;

	SDL_SetRenderDrawColor(renderer, cell['r'], cell['g'], cell['b'], 255);
	SDL_RenderFillRect(renderer, &gridCell);
}

void Gui::drawFilledCells(vector<map<char, int>> filledCells) {
	for (map<char, int> cell : filledCells)
		fillCell(cell);
}

void Gui::loop() {
	Game game(GRID_ROWS, GRID_COLUMNS);
	SDL_Event event;
	bool simulating = false;

	// While user hasn't closed the window
	while (event.type != SDL_QUIT) {
		// Poll for events on queue
		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_KEYDOWN) {
				SDL_Keycode keyCode = event.key.keysym.sym;			

				if (keyCode == SDLK_SPACE)
					simulating = !simulating;

				else if (keyCode == SDLK_n && !simulating)
					game.step();

				else if (keyCode == SDLK_r && !simulating)
					game.reset();

			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				unsigned char buttonCode = event.button.button;

				if (buttonCode == SDL_BUTTON_LEFT && !simulating) {
					game.toggleCell(event.button.x / CELL_SIZE, event.button.y / CELL_SIZE);
				}
			}
		}

		if (simulating) {
			time_point<system_clock> currentTime = system_clock::now();

			if (currentTime > nextStepDue) {
				game.step();
				nextStepDue = currentTime + milliseconds(500);
			}
		}

		drawGame(game);
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