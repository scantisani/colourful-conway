#include "cell_test_headers.h"

BOOST_AUTO_TEST_CASE(defaultCellConstructor_initializesCorrectValues) {
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

BOOST_AUTO_TEST_CASE(seededCellConstructor_initializesCorrectValues) {
	Cell cell(1, 2, 1);

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

BOOST_AUTO_TEST_CASE(cellRespawn_makesCellAlive) {
	Cell cell(1, 2);
	cell.respawn();
	BOOST_CHECK(cell.isAlive());
}

BOOST_AUTO_TEST_CASE(cellKill_makesCellDead) {
	Cell cell(1, 2);
	cell.respawn();
	cell.kill();
	BOOST_CHECK(!cell.isAlive());
}

BOOST_AUTO_TEST_CASE(cellBreed_producesGenesInCorrectRange) {
	vector<int> seeds;
	for (int i = 0; i < 100; ++i) { seeds.push_back(i); };

	Cell parent1(1, 1), parent2(1, 2), parent3(1, 3);

	for (int seed : seeds) {
		Cell child(2, 2, seed);
		vector<Cell> parents = { parent1, parent2, parent3 };

		child.breed(parents);

		BOOST_CHECK(child.isAlive());

		vector<int> cellPhenotype = child.getPhenotype();
		for (int gene : cellPhenotype) {
			BOOST_CHECK_GE(gene, 0);
			BOOST_CHECK_LE(gene, 2);
		}
	}
}