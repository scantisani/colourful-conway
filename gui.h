#ifndef GUI_H
#define GUI_H value

#include <chrono>
#include <SDL2/SDL.h>
#include <vector>
using std::vector;

#include "game.h"

class Gui {
public:
	Gui();
	~Gui();

	void loop();

private:
	// Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	// Grid cell size constant
	const int CELL_SIZE = 10;

	const int GRID_ROWS = SCREEN_WIDTH / CELL_SIZE;
	const int GRID_COLUMNS = SCREEN_HEIGHT / CELL_SIZE;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	std::chrono::time_point<std::chrono::system_clock> nextStepDue;

	void initSDL();
	SDL_Window* initWindow();
	SDL_Renderer* initRenderer();
	void closeSDL();

	void drawGame(Game game);
	void drawGrid();
	void fillCell(int x, int y);
	void drawFilledCells(vector<vector<int>> filledCells);
};

#endif