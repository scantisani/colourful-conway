#ifndef GAME_H
#define GAME_H

#include <vector>

class Game {
public:
	Game(int grid_rows, int grid_columns);
	~Game();

	void toggleCell(int x, int y);
	void createCell(int x, int y);
	void destroyCell(int x, int y);

	std::vector <std::vector <bool>> cells;
};

#endif