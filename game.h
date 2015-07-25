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
		bool alive = false;
		int liveNeighbours = 0;

		bool dominantRedGene = false;
		bool dominantGreenGene = false;
		bool dominantBlueGene = false;
	};
	
	std::vector <std::vector <Cell>> cells;

	void createCell(int x, int y);
	void createCell(Cell &cell);
	void destroyCell(int x, int y);
	void destroyCell(Cell &cell);
	std::vector<Cell> getLiveNeighbours(int x, int y);
};

#endif