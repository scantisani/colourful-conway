#ifndef CELL_H
#define CELL_H

#include <map>
#include <vector>

class Cell {
public:
	Cell(int x, int y, int seed);
	Cell(int x, int y);

	void kill();
	void respawn();

	void breed(std::vector<Cell> parents);

	bool isAlive();
	std::vector<int> getPhenotype();

	const int x, y;

	int liveNeighbours = 0;

private:
	bool alive = false;

	std::map<char, std::vector<int>> genes;

	int getRandomAllele(char gene);
};

#endif