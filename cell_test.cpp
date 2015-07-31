#define BOOST_TEST_MODULE cell

#include "boost/test/included/unit_test.hpp"
#include "cell.h"

#include <vector>
using std::vector;

BOOST_AUTO_TEST_CASE(constructor_test) {
	Cell cell(1, 2);
	BOOST_CHECK_EQUAL(cell.x, 1);
	BOOST_CHECK_EQUAL(cell.y, 2);
	BOOST_CHECK(!cell.isAlive());
	BOOST_CHECK_EQUAL(cell.liveNeighbours, 0);

	vector<int> cellPhenotype = cell.getPhenotype();
	vector<int> defaultPhenotype = { 2, 2, 2 };
	BOOST_CHECK_EQUAL_COLLECTIONS(
		cellPhenotype.begin(), cellPhenotype.end(),
		defaultPhenotype.begin(), defaultPhenotype.end()
	);
}

BOOST_AUTO_TEST_CASE(respawn_test) {
	Cell cell(1, 2);
	cell.respawn();
	BOOST_CHECK(cell.isAlive());
}

BOOST_AUTO_TEST_CASE(kill_test) {
	Cell cell(1, 2);
	cell.respawn();
	cell.kill();
	BOOST_CHECK(!cell.isAlive());
}

BOOST_AUTO_TEST_CASE(breed_test) {
	Cell parent1(1, 1);
	Cell parent3(1, 3);
	Cell parent2(2, 1);

	Cell child(1, 2);
	vector<Cell> parents = { parent1, parent2, parent3 };
	child.breed(parents);

	BOOST_CHECK(child.isAlive());
}