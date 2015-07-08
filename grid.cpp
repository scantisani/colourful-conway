#include <SDL2/SDL.h>
#include <iostream>
using std::cout; using std::endl;
using std::cerr;

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string; using std::to_string;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Grid cell size constant
const int CELL_SIZE = 10;

// SDL initialization and termination functions
void initSDL();
void closeSDL(SDL_Window* window, SDL_Renderer* renderer);

// SDL window initializer function
SDL_Window* initWindow();
// SDL renderer initializer function
SDL_Renderer* initRenderer(SDL_Window* window);

// function to draw the grid for the cells
void drawGrid(SDL_Renderer* renderer);

void initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		string sdl_error = SDL_GetError();
		throw runtime_error("SDL could not initialize! SDL Error: " + sdl_error);
	}
}

SDL_Window* initWindow() {
	SDL_Window* window = SDL_CreateWindow("Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		string sdl_error = SDL_GetError();
		throw runtime_error("Window could not be created! SDL Error: " + sdl_error);
	}

	return window;
}

SDL_Renderer* initRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		string sdl_error = SDL_GetError();
		throw runtime_error("Renderer could not be created! SDL Error: " + sdl_error);
	}

	return renderer;
}

void closeSDL(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

void drawGrid(SDL_Renderer* renderer) {
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

void fillCell(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect cell;
	// x and y are top left corner of cell mouse pointer is in
	cell.x = x - (x % CELL_SIZE) + 1; // 1-pixel buffer so as not to erase grid lines
	cell.y = y - (y % CELL_SIZE) + 1;
	cell.w = CELL_SIZE - 1;
	cell.h = CELL_SIZE - 1;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(renderer, &cell);
}

int main(int argc, char const *argv[]) {
	try {
		SDL_Event event;
		SDL_Window* window = initWindow();
		SDL_Renderer* renderer = initRenderer(window);

		drawGrid(renderer);

		// While user hasn't closed the window
		while (event.type != SDL_QUIT) {
			// Poll for events on queue
			SDL_PollEvent(&event);

			if (event.button.type == SDL_MOUSEBUTTONDOWN) {
				fillCell(renderer, event.button.x, event.button.y);
			}
			// Refresh window
			SDL_RenderPresent(renderer);
		}

		closeSDL(window, renderer);
	} catch (runtime_error e) {
		cerr << e.what() << endl;
	}

	return 0;
}