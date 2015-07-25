#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>

class Game {
public:
	Game(int grid_rows, int grid_columns);
	~Game();

	void toggleCell(int x, int y);
	void step();
	void reset();
	std::vector<std::map<char, int>> getLiveCells();

private:
	struct Cell {
		const int x;
		const int y;

		Cell(int x, int y)	: x(x), y(y) {};

		bool alive = false;
		int liveNeighbours = 0;

		int redGene = 0;
		int greenGene = 0;
		int blueGene = 0;
	};
	
	std::vector <std::vector <Cell>> cells;

	void createCell(Cell &cell);
	void destroyCell(Cell &cell);
	std::vector<Cell> getLiveNeighbours(Cell &cell);
};

#endif