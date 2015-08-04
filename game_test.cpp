#include "game_test_headers.h"

struct gameFixture {
	gameFixture() : game(5, 5) { }
	~gameFixture() { }

	Game game;
};

BOOST_FIXTURE_TEST_SUITE(gameSuite, gameFixture);

BOOST_AUTO_TEST_CASE(gameConstructor_createsGridOfDeadCells) {
	int numberOfLiveCells = game.getLiveCells().size();
	BOOST_CHECK_EQUAL(numberOfLiveCells, 0);
}

BOOST_AUTO_TEST_CASE(gameToggleCell_killsAndRevivesCell) {
	int liveCells = game.getLiveCells().size();

	game.toggleCell(1, 1);
	BOOST_CHECK_EQUAL(game.getLiveCells().size(), liveCells + 1);
	game.toggleCell(1, 1);
	BOOST_CHECK_EQUAL(game.getLiveCells().size(), liveCells);
}

BOOST_AUTO_TEST_CASE(gameReset_killsAllCells) {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			game.toggleCell(i, j);
	}

	game.reset();
	BOOST_CHECK_EQUAL(game.getLiveCells().size(), 0);
}

BOOST_AUTO_TEST_CASE(gameGetLiveCells_passesLiveCells) {
	game.toggleCell(1, 2);
	Cell liveCell = game.getLiveCells()[0];

	BOOST_CHECK_EQUAL(liveCell.x, 1);
	BOOST_CHECK_EQUAL(liveCell.y, 2);
}

BOOST_AUTO_TEST_CASE(gameStep_killsCells_withNoNeighbours) {
	game.toggleCell(1, 1);
	game.step();

	BOOST_CHECK_EQUAL(game.getLiveCells().size(), 0);
}

BOOST_AUTO_TEST_CASE(gameStep_killsCells_withOneNeighbour) {
	// cells with one neighbour (each other)
	game.toggleCell(1, 1);
	game.toggleCell(1, 2);

	game.step();

	BOOST_CHECK_EQUAL(game.getLiveCells().size(), 0);
}

BOOST_AUTO_TEST_CASE(gameStep_ignoresLiveCells_withTwoNeighbours) {
	// cells that each have two neighbours
	game.toggleCell(1, 1);
	game.toggleCell(1, 2);
	game.toggleCell(2, 1);

	game.step();

	vector<Cell> liveCells = game.getLiveCells();
	int found = 0;

	// check our original three cells are still alive
	for (Cell cell : liveCells) {
		if	(
			(cell.x == 1 && cell.y == 1) ||
			(cell.x == 1 && cell.y == 2) ||
			(cell.x == 2 && cell.y == 1)
			) {
			++found;
		}
	}

	BOOST_CHECK_EQUAL(found, 3);
}

BOOST_AUTO_TEST_CASE(gameStep_ignoresDeadCells_withTwoNeighbours) {
	game.toggleCell(1, 1);
	game.toggleCell(1, 3);
	// dead cell: 1, 2

	game.step();

	vector<Cell> liveCells = game.getLiveCells();

	for (Cell cell : liveCells)
		BOOST_CHECK(!(cell.x == 1 && cell.y == 2));
}


BOOST_AUTO_TEST_CASE(gameStep_ignoresLiveCells_withThreeNeighbours) {
	// cells that each have two neighbours
	game.toggleCell(1, 1);
	game.toggleCell(1, 2);
	game.toggleCell(2, 1);

	game.step();

	vector<Cell> liveCells = game.getLiveCells();
	int found = 0;

	// check our original three cells are still alive
	for (Cell cell : liveCells) {
		if	(
			(cell.x == 1 && cell.y == 1) ||
			(cell.x == 1 && cell.y == 2) ||
			(cell.x == 2 && cell.y == 1)
			) {
			++found;
		}
	}

	BOOST_CHECK_EQUAL(found, 3);
}

BOOST_AUTO_TEST_CASE(gameStep_respawnsCells_withThreeNeighbours) {
	game.toggleCell(1, 1);
	game.toggleCell(1, 2);
	game.toggleCell(2, 1);
	// dead cell: 2, 2

	game.step();

	vector<Cell> liveCells = game.getLiveCells();
	bool respawned = false;

	for (Cell cell : liveCells) {
		if (cell.x == 2 && cell.y == 2)
			respawned = true;
	}

	BOOST_CHECK(respawned);
}

BOOST_AUTO_TEST_CASE(gameStep_killsCells_withFourNeighbours) {
	game.toggleCell(2, 2);

	game.toggleCell(1, 2);
	game.toggleCell(3, 2);
	game.toggleCell(2, 1);
	game.toggleCell(2, 3);

	game.step();

	vector<Cell> liveCells = game.getLiveCells();

	for (Cell cell : liveCells)
		BOOST_CHECK(!(cell.x == 2 && cell.y == 2));
}

BOOST_AUTO_TEST_SUITE_END();