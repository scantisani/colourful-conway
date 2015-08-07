#include <algorithm>
using std::max_element;

#include <vector>
using std::vector;

#include "cell.h"

Cell::Cell(int x, int y, int seed) : x(x), y(y) {
	genes['r'] = { 2, 1, 0 };
	genes['g'] = { 2, 1, 0 };
	genes['b'] = { 2, 1, 0 };

	srand(seed);
}

Cell::Cell(int x, int y) : Cell(x, y, time(NULL)) {}

void Cell::kill() {
	alive = false;
	genes['r'] = { 2, 1, 0 };
	genes['g'] = { 2, 1, 0 };
	genes['b'] = { 2, 1, 0 };
}

void Cell::respawn() {
	alive = true;
}

void Cell::breed(vector<Cell> parents) {
	alive = true;

	for (int i = 0; i < 3; ++i) {
		genes['r'][i] = parents[i].getRandomAllele('r');
		genes['g'][i] = parents[i].getRandomAllele('g');
		genes['b'][i] = parents[i].getRandomAllele('b');
	}

	tryMutation();
}

bool Cell::isAlive() {
	return alive;
}

vector<int> Cell::getPhenotype() {
	vector<int> &r = genes['r'];
	vector<int> &g = genes['g'];
	vector<int> &b = genes['b'];

	return {	*max_element(r.begin(), r.end()),
				*max_element(g.begin(), g.end()),
				*max_element(b.begin(), b.end())
			};
}

int Cell::getRandomAllele(char gene) {
	return genes[gene][rand() % 3];
}

void Cell::tryMutation() {
	for (auto it = genes.begin(); it != genes.end(); ++it) {
		vector<int> &gene = it->second;

		for (int &allele : gene) {
			int mutationChance = rand() % 100;

			if (mutationChance >= 99)
				allele = rand() % 3;
		}
	}
}
