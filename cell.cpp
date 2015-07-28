#include <algorithm>
using std::max_element;

#include <vector>
using std::vector;

#include "cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {
	genes['r'] = { 0, 0, 0 };
	genes['g'] = { 0, 0, 0 };
	genes['b'] = { 0, 0, 0 };
}

void Cell::kill() {
	alive = false;
	genes['r'] = { 0, 0, 0 };
	genes['g'] = { 0, 0, 0 };
	genes['b'] = { 0, 0, 0 };
}

void Cell::respawn() {
	alive = true;
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
