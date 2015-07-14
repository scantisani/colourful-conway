#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "game.h"

Game::Game(int grid_rows, int grid_columns) {
	cells = vector<vector<Cell>>
	(grid_rows, vector<Cell>	// cells is a vector of size grid_rows
		(grid_columns));		// that holds vectors (of Cells) of size grid_columns
}

Game::~Game() {
	cells.clear();
}

void Game::toggleCell(int x, int y) {
	if (cells[x][y].alive)
		destroyCell(x, y);
	else
		createCell(x, y);
}

void Game::createCell(int x, int y) {
	cells[x][y].alive = true;
}

void Game::destroyCell(int x, int y) {
	cells[x][y].alive = false;
}

vector<Game::Cell> Game::getLiveNeighbours(int x, int y) {
	vector<Game::Cell> neighbours;

	for (int i : {-1, 0, 1}) {
		for (int j : {-1, 0, 1}) {
			int row = x + i;
			int col = y + j;

			if (row >= 0 && row <= cells.size() - 1 &&		// check row and col are within grid limits
				col >= 0 && col <= cells[0].size() - 1 &&
				!(row == x && col == y)) {					// don't include the cell itself in neighbours
				if (cells[row][col].alive)
					neighbours.push_back(cells[row][col]);
			}
		}
	}

	return neighbours;
}

vector<vector <int>> Game::getFilledCells() {
	vector<vector <int>> filledCells;

	for (int i = 0; i < cells.size(); ++i) {
		for (int j = 0; j < cells[i].size(); ++j) {
			if (cells[i][j].alive) { 
				vector<int> coordinates = { i, j };
				filledCells.push_back(coordinates);
			}
		}
	}

	return filledCells;
}