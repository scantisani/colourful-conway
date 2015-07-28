#ifndef CELL_H
#define CELL_H

#include <map>
#include <vector>

class Cell {
public:
	Cell(int x, int y);

	void kill();
	void respawn();

	bool isAlive();
	std::vector<int> getPhenotype();

	const int x;
	const int y;

	int liveNeighbours = 0;

private:
	bool alive = false;

	std::map<char, std::vector<int>> genes;
};

#endif