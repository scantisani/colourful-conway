#include <SDL2/SDL.h>
#include <iostream>
using std::cout; using std::endl;
using std::cerr;

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Grid cell size constant
const int CELL_SIZE = 5;

// SDL initialization and termination functions
void initSDL();
void closeSDL();

// SDL window initializer function
SDL_Window* initWindow();
// SDL renderer initializer function
SDL_Renderer* initRender();

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

int main(int argc, char const *argv[]) {
	try {
		SDL_Event event;
		SDL_Window* window = initWindow();
		SDL_Renderer* renderer = initRenderer(window);

		// While user hasn't closed the window
		while (event.type != SDL_QUIT) {
			// Poll for events on queue
			SDL_PollEvent(&event);

			// Clear screen
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			// Draw black horizontal lines
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			for (int i = 0; i < SCREEN_HEIGHT; i += CELL_SIZE)
				SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
			// Draw black vertical lines
			for (int i = 0; i < SCREEN_WIDTH; i += CELL_SIZE)
				SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);

			// Update screen
			SDL_RenderPresent(renderer);
		}

		closeSDL(window, renderer);
	} catch (runtime_error e) {
		cerr << e.what() << endl;
	}

	return 0;
}