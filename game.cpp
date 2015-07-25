#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "game.h"

Game::Game(int gridRows, int gridColumns) {
	// initialize 'cells' vector with Cells that
	// know their position in the vector
	for (int i = 0; i < gridRows; ++i) {
		vector<Cell> newCellVector;

		for (int j = 0; j < gridColumns; ++j) {
			Cell newCell = Cell(i, j);
			newCellVector.push_back(newCell);
		}

		cells.push_back(newCellVector);
	}
}

Game::~Game() {
	cells.clear();
}

void Game::toggleCell(int x, int y) {
	Cell &toggledCell = cells[x][y];

	if (toggledCell.alive)
		destroyCell(toggledCell);
	else
		createCell(toggledCell);
}

void Game::createCell(Cell &cell) {
	cell.alive = true;
}

void Game::destroyCell(Cell &cell) {
	cell.alive = false;
}

void Game::reset() {
	for (vector<Cell> &row : cells) {
		for (Cell &cell : row)
			destroyCell(cell);
	}
}

vector<Game::Cell> Game::getLiveNeighbours(Cell &cell) {
	vector<Cell> neighbours;

	for (int i : {-1, 0, 1}) {
		for (int j : {-1, 0, 1}) {
			int row = cell.x + i;
			int col = cell.y + j;

			bool withinGridLimits = (	row >= 0 && row < cells.size() &&
										col >= 0 && col < cells[0].size()
									);
			bool neighbourNotItself = !(row == cell.x && col == cell.y); 

			if (withinGridLimits && neighbourNotItself) {
				Cell &neighbour = cells[row][col];

				if (neighbour.alive)
					neighbours.push_back(neighbour);
			}
		}
	}

	return neighbours;
}

vector<map<char, int>> Game::getLiveCells() {
	vector<map<char, int>> liveCells;

	for (vector<Cell> &row : cells) {
		for (Cell &cell : row) {

			if (cell.alive) {
				uint8_t red =	cell.redGene	* 127;
				uint8_t green =	cell.greenGene	* 127;
				uint8_t blue =	cell.blueGene	* 127;

				map<char, int> cellInfo {
					{'x', cell.x },
					{'y', cell.y },
					{'r', red },
					{'g', green },
					{'b', blue },
				};

				liveCells.push_back(cellInfo);
			}
		}
	}

	return liveCells;
}

void Game::step() {
	for (vector<Cell> &row : cells) {
		for (Cell &cell : row)
			cell.liveNeighbours = getLiveNeighbours(cell).size();
	}

	for (vector<Cell> &row : cells) {
		for (Cell &cell : row) {
			if (cell.liveNeighbours < 2) {
				destroyCell(cell);
			}
			else if (cell.liveNeighbours == 3) {
				createCell(cell);
			}
			else if (cell.liveNeighbours > 3) {
				destroyCell(cell);
			}
		}
	}
}