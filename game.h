#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>

#include "cell.h"

class Game {
public:
	Game(int grid_rows, int grid_columns);
	~Game();

	void toggleCell(int x, int y);
	void step();
	void reset();
	std::vector<Cell> getLiveCells();

private:
	const int GRID_ROWS, GRID_COLUMNS;

	std::vector <std::vector <Cell>> cells;
	std::vector<Cell> getLiveNeighbours(Cell &cell);
};

#endif