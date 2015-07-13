#ifndef GAME_H
#define GAME_H

#include <vector>

class Game {
public:
	Game(int grid_rows, int grid_columns);
	~Game();

	void toggleCell(int x, int y);
	std::vector<std::vector <int>> getFilledCells();

private:
	struct Cell {
		bool alive = 0;
	};
	
	std::vector <std::vector <Cell>> cells;

	void createCell(int x, int y);
	void destroyCell(int x, int y);
};

#endif