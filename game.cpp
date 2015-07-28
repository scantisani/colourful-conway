#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "cell.h"
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

	if (toggledCell.isAlive())
		toggledCell.kill();
	else
		toggledCell.respawn();
}

void Game::reset() {
	for (vector<Cell> &row : cells) {
		for (Cell &cell : row)
			cell.kill();
	}
}

vector<Cell> Game::getLiveNeighbours(Cell &cell) {
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

				if (neighbour.isAlive())
					neighbours.push_back(neighbour);
			}
		}
	}

	return neighbours;
}

vector<Cell> Game::getLiveCells() {
	vector<Cell> liveCells;

	for (vector<Cell> &row : cells) {
		for (Cell &cell : row) {
			if (cell.isAlive())
				liveCells.push_back(cell);
		}
	}

	return liveCells;
}

void Game::step() {
	for (vector<Cell> &row : cells) {
		for (Cell &cell : row)
			cell.liveNeighbours = getLiveNeighbours(cell).size();
	}

	vector<vector<Cell>> newCells = cells;

	for (unsigned int i = 0; i < cells.size(); ++i) {
		for (unsigned int j = 0; j < cells[i].size(); ++j) {
			Cell &cell = cells[i][j];
			Cell &newCell = newCells[i][j];

			if (cell.liveNeighbours < 2)
				newCell.kill();

			else if (cell.liveNeighbours == 3 && !cell.isAlive())
				newCell.breed(getLiveNeighbours(cell));

			else if (cell.liveNeighbours > 3)
				newCell.kill();

		}
	}

	cells.swap(newCells);
}