#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "game.h"

Game::Game(int gridRows, int gridColumns) {
	cells = vector<vector<Cell>>
	(gridRows, vector<Cell>	// cells is a vector of size gridRows
		(gridColumns));		// that holds vectors (of Cells) of size gridColumns
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

void Game::createCell(Cell &cell) {
	cell.alive = true;
}

void Game::destroyCell(int x, int y) {
	cells[x][y].alive = false;
}

void Game::destroyCell(Cell &cell) {
	cell.alive = false;
}

vector<Game::Cell> Game::getLiveNeighbours(int x, int y) {
	vector<Cell> neighbours;

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

void Game::step() {
	for (unsigned int i = 0; i < cells.size(); ++i) {
		for (unsigned int j = 0; j < cells[i].size(); ++j) {
			cells[i][j].liveNeighbours = getLiveNeighbours(i, j).size();
		}
	}

	for (vector<Cell> &row : cells) {
		for (Cell &cell : row) {
			if (cell.liveNeighbours < 2) {
				destroyCell(cell);
			}
			else if (cell.liveNeighbours == 3) {
				createCell(cell);
			}
			else if (cell. liveNeighbours > 3) {
				destroyCell(cell);
			}
		}
	}
}