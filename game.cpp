#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include "game.h"

Game::Game(int grid_rows, int grid_columns) {
	// cells is a vector of vectors of booleans; each boolean starts as 0
	// lower-level vectors are of size [grid_columns], higher-level of size [grid_rows]
	cells = vector< vector<bool> >
	(grid_rows, vector<bool>
		(grid_columns, 0));
}

Game::~Game() {
	cells.clear();
}

void Game::toggleCell(int x, int y) {
	if (cells[x][y] == 0)
		createCell(x, y);
	else
		destroyCell(x, y);
}

void Game::createCell(int x, int y) {
	cells[x][y] = 1;
	cout << "Cell created: " << x << " " << y << endl;
}

void Game::destroyCell(int x, int y) {
	cells[x][y] = 0;
	cout << "Cell destroyed: " << x << " " << y << endl;
}

vector<vector <int>> Game::getFilledCells() {
	vector<vector <int>> filledCells;

	for (int i = 0; i < cells.size(); ++i) {
		for (int j = 0; j < cells[i].size(); ++j) {
			if (cells[i][j] == 1) { 
				vector<int> coordinates = { i, j };
				filledCells.push_back(coordinates);
			}
		}
	}

	return filledCells;
}